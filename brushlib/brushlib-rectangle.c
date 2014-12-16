/*
 * brushlib - include license
 */

#include <stdlib.h>
#include <string.h>

#include <brushlib-rectangle.h>

void *
memdup(const void *src, size_t len)
{
  void *p = malloc(len);
  if (p)
    memcpy(p, src, len);
  return p;
}

BrushLibRectangle *
brushlib_rectangle_copy(BrushLibRectangle *self)
{
  return (BrushLibRectangle *)memdup(self, sizeof(BrushLibRectangle));
}

void
brushlib_rectangle_expand_to_include_point(BrushLibRectangle *self, int x, int y)
{
  if (self->width == 0) {
    self->width = 1;
    self->height = 1;
    self->x = x;
    self->y = y;
  } else {
    if (x < self->x) {
      self->width += self->x - x;
      self->x = x;
    } else if (x >= self->x + self->width) {
      self->width = x - self->x + 1;
    }

    if (y < self->y) {
      self->height += self->y - y;
      self->y = y;
    } else if (y >= self->y + self->height) {
      self->height = y - self->y + 1;
    }
  }
}
