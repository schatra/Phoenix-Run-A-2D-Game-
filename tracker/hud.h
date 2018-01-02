#ifndef HUD__H
#define HUD__H
#include <SDL.h>
#include<string>
#include<stdint.h>
#include "drawable.h"
#include "clock.h"
#include "ioMod.h"



class Hud {
public:
  static Hud& getInstance();  
  ~Hud();
  void displayHud() const;
  void displayLost(int count) const;
  void displayWin(int count) const;
void printHealth(int lives) const;
private:

  const int width;
  const int height;
  int x;
  int y;
  SDL_Rect Rectangle;
  SDL_Renderer* renderer;
  Hud();
  Hud(const Hud&);
  Hud& operator=(const Hud&);
  };
#endif


