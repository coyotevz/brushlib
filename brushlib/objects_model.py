# -*- coding: utf-8 -*-

class PenInfo(object):

    x = 0
    y = 0
    pressure = 0
    xtilt = 0
    ytilt = 0
    dtime = 0

class BrushSetting(object):

    cname = None
    name = None
    constant = None
    min = 0
    default = 0
    max = 0
    tooltip = None

    def get_name(self):
        pass

    def get_tooltip(self):
        pass


class Brush(object):

    def new(self):
        pass

    def reset(self):
        pass

    def new_stroke(self):
        pass

    def stroke_to(self, surface: Surface, pen_info: PenInfo):
        pass

    def set_base_value(self, id: BrushSetting, value):
        pass

    def get_base_value(self, id: BrushSetting):
        pass

    def is_constant(self, id: BrushSetting):
        pass

    def get_inputs_used_n(self, id: BrushSetting):
        pass

    def set_mapping_n(self, id: BrushSetting, input: BrushInput):
        pass

    def get_mapping_n(self, id: BrushSetting, input: BrushInput):
        pass

    def set_mapping_point(self, id: BrushSetting, input: BrushInput, index: int, x, y):
        pass

    def get_mapping_point(self, id: BrushSetting, input: BrushInput, index: int, x, y):
        pass

    def set_state(self, i: BrushState, value):
        pass

    def get_state(self, i: BrushState):
        pass

    def get_total_stroke_painting_time(self):
        pass

    def set_print_inputs(self, enabled: boolean):
        pass

    def from_defults(self):
        pass

    def from_string(self, string: const char):
        pass

class Mapping(object):

    def get_base_value(self):
        pass

    def set_base_value(self, value):
        pass

    def get_n(self, input: int):
        pass

    def set_n(self, input: int, n: int):
        pass

    def set_point(self, input: int, index: int, x, y):
        pass

    def get_point(self, input: int, index: int, x, y):
        pass

    def is_constant(self):
        pass

    def get_input_used_n(self):
        pass

    def calculate(self, data):
        pass

    def calculate_single_input(self, input):
        pass

class Surface(object):
    
    def draw_dab(self, x, y, radius, color_r, color_g, color_b, opaque, hardness,
                 alpha_eraser, aspect_ratio, angle, lock_alpha, colorize):
        pass

    def get_color(self, x, y, radius, color_r: out, color_g: out, color_b: out,
                  color_a: out):
        pass

    def get_alpha(self, x, y, radius):
        pass

    def save_png(self, path, x, y, width, height):
        pass

    def begin_atomic(self):
        pass

    def end_atomic(self):
        pass


class TiledSurface(Surface):

    def set_symmetry_state(self, active, center_x):
        pass

    def tile_request_start(self, request: TileRequest):
        pass

    def tile_request_end(self, request: TileRequest):
        pass
