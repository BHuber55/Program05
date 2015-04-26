#if !defined SONG_H
#define SONG_H

#include "Text.h"
using CSC2110::String;

namespace CSC2110
{
class Song
{
   private:
      String* title;
      String* length;

   public:
      Song(String* title, String* length);
      virtual ~Song();
      void displaySong();
};
}

#endif
