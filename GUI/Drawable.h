#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>

class Drawable
{
   private:

   public:
      Drawable() {};
      virtual ~Drawable() {};
      virtual void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height) = 0;
      virtual void mouseClicked(int x, int y) = 0;
};

#endif
