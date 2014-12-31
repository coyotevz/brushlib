# -*- coding: utf-8 -*-

from collections import namedtuple
import math

EPSILON = 1e-5
EPSILON2 = EPSILON ** 2

MIN_MOV = 4.0

def set_min_mov(val):
    global MIN_MOV
    assert val > 0
    MIN_MOV = val

def cached_property(func):
    name = func.__name__
    doc = func.__doc__

    def getter(self, name=name):
        try:
            return self.__dict__[name]
        except KeyError:
            self.__dict__[name] = value = func(self)
            return value
    getter.func_name = name
    return property(getter, doc=doc)

def cos_sin_deg(deg):
    deg = deg % 360.0
    if deg == 90.0:
        return 0.0, 1.0
    elif deg == 180.0:
        return -1.0, 0.0
    elif deg == 270.0:
        return 0.0, -1.0
    rad = math.radians(deg)
    return math.cos(rad), math.sin(rad)

class Affine(namedtuple('Affine', 'a b c d e f g h i')):

    def __new__(self, *members):
        if len(members) == 6:
            mat3x3 = [x * 1.0 for x in members] + [0.0, 0.0, 1.0]
            return tuple.__new__(Affine, mat3x3)
        else:
            raise TypeError(
                "Expected 6 coefficients, found %d" % len(members))

    @classmethod
    def identity(cls):
        return identity

    @classmethod
    def translation(cls, xoff, yoff):
        return tuple.__new__(cls,
            (1.0, 0.0, xoff,
             0.0, 1.0, yoff,
             0.0, 0.0, 1.0))

    @classmethod
    def scale(cls, *scaling):
        if len(scaling) == 1:
            sx = sy = float(scaling[0])
        else:
            sx, sy = scaling
        return tuple.__new__(cls,
            (sx, 0.0, 0.0,
             0.0, sy, 0.0,
             0.0, 0.0, 1.0))

    @classmethod
    def rotation(cls, angle, pivot=None):
        ca, sa = cos_sin_deg(angle)
        if pivot is None:
            return tuple.__new__(cls,
                (ca, sa, 0.0,
                 -sa, ca, 0.0,
                 0.0, 0.0, 1.0))
        else:
            px, py = pivot
            return tuple.__new__(cls,
                (ca, sa, px - px*ca + py*sa,
                 -sa, ca, py - px*sa - py*ca,
                 0.0, 0.0, 1.0))

    def __repr__(self):
        return ("Affine(%r, %r, %r,\n"
                "       %r, %r, %r)") % self[:6]

    @cached_property
    def determinant(self):
        a, b, c, d, e, f, g, h, i = self
        return a*e - b*d

    def is_identity(self):
        return self is identity or self.almost_equals(identity)

    def almost_equals(self, others):
        for i in (0, 1, 2, 3, 4, 5):
            if abs(self[i] - other[i]) >= EPSILON:
                return False
        return True

    def __mul__(self, other):
        sa, sb, sc, sd, se, sf, _, _, _ = self
        if isinstance(other, Affine):
            oa, ob, oc, od, oe, of, _, _, _ = other
            return tuple.__new__(Affine,
                (sa*oa + sb*od, sa*ob + sb*oe, sa*oc + sb*of + sc,
                 sd*oa + se*od, sd*ob + se*oe, sd*oc + sb*of + sf,
                 0.0, 0.0, 1.0))
        else:
            try:
                vx, vy = other
            except Exception:
                return NotImplemented
            return (vx * sa + vy * sd + sc, vx * sb + vy * se + sf)

identity = Affine(1, 0, 0, 0, 1, 0)


class Point(namedtuple('Point', 'x y')):

    def __sub__(self, other):
        sx, sy = self
        try:
            ox, oy = other
        except Exception:
            return NotImplemented
        return tuple.__new__(Point, (sx - ox, sy - oy))

    def __add__(self, other):
        sx, sy = self
        try:
            ox, oy = other
        except Exception:
            return NotImplemented
        return tuple.__new__(Point, (sx + ox, sy + oy))

    def __rsub__(self, other):
        return self.__sub__(other)

    def __radd__(self, other):
        return self.__add__(other)


class Line(namedtuple('Line', 'p1 p2')):

    @property
    def dx(self):
        return self.p1.x - self.p2.x

    @property
    def dy(self):
        return self.p1.y - self.p2.y

    def translated(self, affine):
        return tuple.__new__(Line, (Point(*(affine * self.p1)), Point(*(affine * self.p2))))


class Ruler(Line):

    def project(self, point):
        p1, p2 = self
        a1 = (p2.y - p1.y) / (p2.x - p1.x)
        b1 = p1.y - p1.x * a1
        a2 = (p2.x - p1.x) / (p1.y - p2.y)
        b2 = point.y - a2 * point.x
        xm = (b2 - b1) / (a1 - a2)
        return Point(xm, xm * a1 + b1)

    def project2(self, point):
        snap_line = Line(*self)
        dx, dy = snap_line.dx, snap_line.dy
        dx2, dy2 = dx**2, dy**2
        x = (dx2 * point.x + dy2 * snap_line.p1.x + dx * dy * (point.y - snap_line.p1.y)) / (dx2 + dy2)
        y = (dx2 * snap_line.p1.y + dy2 * point.y + dx * dy * (point.x - snap_line.p1.x)) / (dx2 + dy2)
        return Point(x, y)


class ParallelRuler(Line):

    def project(self, point, stroke_begin):
        dx, dy = point - stroke_begin
        if (dx*dx + dy*dy) < MIN_MOV:
            # allow some movement before snapping
            return stroke_begin
        snap_line = Line(*self)
        translation = Affine.translation(*(stroke_begin - self.p1))
        snap_line = snap_line.translated(translation)
        dx, dy = snap_line.dx, snap_line.dy
        dx2, dy2 = dx**2, dy**2
        x = (dx2 * point.x + dy2 * snap_line.p1.x + dx * dy * (point.y - snap_line.p1.y)) / (dx2 + dy2)
        y = (dx2 * snap_line.p1.y + dy2 * point.y + dx * dy * (point.x - snap_line.p1.x)) / (dx2 + dy2)
        return Point(x, y)


class VanishingPoint(Point):

    def project(self, point, stroke_begin):
        dx, dy = point - stroke_begin
        if (dx*dx + dy*dy) < MIN_MOV:
            return stroke_begin
        snap_line = Line(self, stroke_begin)
        dx, dy = snap_line.dx, snap_line.dy
        dx2, dy2 = dx**x2, dy**2
        x = (dx2 * point.x + dy2 * snap_line.p1.x + dx * dy * (point.y - snap_line.p1.y)) / (dx2 + dy2)
        y = (dx2 * snap_line.p1.y + dy2 * point.y + dx * dy * (point.x - snap_line.p1.x)) / (dx2 + dy2)
        return Point(x, y)
