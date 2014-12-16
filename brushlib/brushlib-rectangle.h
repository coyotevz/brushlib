/*
 * brushlib - fill license
 */

#if !defined(__BRUSHLIB_H_INSIDE__) && !defined(BRUSHLIB_COMPILATION)
#error "Only <brushlib/brushlib.h> can be included directly."
#endif

#ifndef __BRUSHLIB_RECTANGLE_H__
#define __BRUSHLIB_RECTANGLE_H__

G_BEGIN_DECLS

typedef struct {
  int x;
  int y;
  int width;
  int height;
} BrushLibRectangle;

void brushlib_rectangle_expand_to_include_point(BrushLibRectangle *self, int x, int y);

BrushLibRectangle *
brushlib_rectangle_copy(BrushLibRectangle *self);

G_END_DECLS

#endif /* __BRUSHLIB_RECTANGLE_H__ */
