#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include "Drawable.h"

#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>

class DrawPanel : public Gtk::DrawingArea
{
   private:
      int width;
      int height;

      Drawable* drawable;
      virtual void drawBackground(Cairo::RefPtr<Cairo::Context> cr);

   public:
      DrawPanel(int width, int height, Drawable* d);
      virtual ~DrawPanel();
      virtual void render();
      virtual void render(const Cairo::RefPtr<Cairo::Context>& cr);
      virtual bool on_button_press_event(GdkEventButton* event);
      virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
      //virtual bool on_key_press_event(GdkEventKey* event);

   protected:
      //override default signal handler

};

#endif
