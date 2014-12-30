# -*- coding: utf-8 -*-

from collections import namedtuple
import math

EPSILON = 1e-5
EPSILON2 = EPSILON ** 2

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
