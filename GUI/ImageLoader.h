#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <gtkmm/drawingarea.h>

class ImageLoader
{
   public:
      static Glib::RefPtr<Gdk::Pixbuf> loadImageRGB(const char* id);
      static Glib::RefPtr<Gdk::Pixbuf> loadImageRGBA(const char* id);
};

#endif 
