#ifndef CIRCLE_H
#define CIRCLE_H

#include "Color.h"
#include "../CSC2110/Text.h"
#include <gtkmm.h>

class Circle 
{
   private:
      int radius;
      Color* color;
      CSC2110::String* text;
      static const float PI2 = 6.283854;

   public:
      Circle(Color* color, int radius, CSC2110::String* text);
      ~Circle();
      void draw(Cairo::RefPtr<Cairo::Context> cr, int x, int y);
};

#endif