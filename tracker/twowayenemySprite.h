#ifndef TWOWAYENEMYSPRITE__H
#define TWOWAYENEMYSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class ExplodingSprite;

class TwoWayEnemySprite : public Drawable {
public:
  TwoWayEnemySprite(const std::string&, const std::string&);
  TwoWayEnemySprite(const TwoWayEnemySprite&);

    ~TwoWayEnemySprite();

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { 
    return images[currentFrame]; 
  }
  int getScaledWidth()  const { 
    return getScale()*images[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*images[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return images[currentFrame]->getSurface();
  }

  void Images_set(std::vector<Image *> Imagesnew) {
    images = Imagesnew;
  }

void reset();
 virtual void explode();
bool deleteenemy() const { 
 
return deletesprite; }

protected:
  std::vector<Image *> images;
ExplodingSprite* explosion;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  std::string rightsprite;
  std::string leftsprite;
bool deletesprite;
  void advanceFrame(Uint32 ticks);
  TwoWayEnemySprite& operator=(const TwoWayEnemySprite&);
Vector2f makeVelocity(int, int) const;
};
#endif
