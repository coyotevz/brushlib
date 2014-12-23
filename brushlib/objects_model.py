# -*- coding: utf-8 -*-

class PenInfo(object):

    x = 0
    y = 0
    pressure = 0
    xtilt = 0
    ytilt = 0
    dtime = 0

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
