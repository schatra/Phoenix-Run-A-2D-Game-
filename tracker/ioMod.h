#ifndef IOMOD__H
#define IOMOD__H
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class IOmod {
public:
  static IOmod& getInstance();
  ~IOmod();
  SDL_Texture* readTexture(const std::string& filename);
  SDL_Surface* readSurface(const std::string& filename);
 void writeText(const std::string&, int, int) const;
  void writeText(const std::string&,SDL_Color&, int, int) const;
//  void writeText(const std::string& msg, int x, int y,SDL_Color txtcolor, int fontSize) const ;
  SDL_Renderer* getRenderer() const { return renderer; }
private:
  int init;
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Color textColor;
  IOmod();
  IOmod(const IOmod&);
  IOmod& operator=(const IOmod&);
};
#endif
