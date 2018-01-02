#ifndef POOLHUD__H
#define POOLHUD__H
#include "ioMod.h"
#include "shootingSprite.h"



class PoolHud {
public:
  PoolHud(const ShootingSprite&);
  void draw() const;
  void update();
  void toggle() { showPoolHud= !showPoolHud;}
  PoolHud(const PoolHud&)= delete;
  PoolHud& operator=(const PoolHud&)=delete;
private:

  const ShootingSprite& player;
  SDL_Renderer* r;
  SDL_Rect Rectangle;
  bool showPoolHud;
  IOmod& io;
  };
#endif

