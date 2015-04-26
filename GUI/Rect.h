#ifndef RECT_H
#define RECT_H

#include "Color.h"
#include <gtkmm.h>

class Rect
{
   private:
      int width;
      int height;
      Color* color;

   public:
      Rect(Color* color, int width, int height);
      virtual ~Rect();
      void draw(Cairo::RefPtr<Cairo::Context> cr, int x, int y);
};

#endif

