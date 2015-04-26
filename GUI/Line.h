#if !defined (LINE_H)
#define LINE_H

#include "Color.h"
#include <gtkmm.h>

class Line
{
   private:
      Color* color;
      double line_width;

   public:
      Line(Color* color, double line_width);
      ~Line();
      void draw(Cairo::RefPtr<Cairo::Context> cr, int x1, int y1, int x2, int y2);
};

#endif
