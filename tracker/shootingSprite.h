#ifndef SHOOTINGSPRITE_H
#define SHOOTINGSPRITE_H

#include <string>
#include <iostream>
#include <list>
#include "player.h"
#include "bullet.h"
#include "bulletsPool.h"

class ShootingSprite : public Player {
public:
  ShootingSprite(const std::string&,const std::string&);
  ShootingSprite(const ShootingSprite& s);
  virtual void update(Uint32 ticks);
  virtual void draw() const;
  void shoot();
void shootleft();
  unsigned int bulletCount() const { return bullets.bulletCount(); }
  unsigned int freeCount()  const { return bullets.freeCount(); }
ShootingSprite& operator=(const ShootingSprite&)=delete;
  bool collidedB(const Drawable*) const;
private:
  std::string bulletName;
  BulletsPool bullets;
  float minSpeed;
  float bulletInterval;
  float timeSinceLastFrame;
 
};  
#endif
