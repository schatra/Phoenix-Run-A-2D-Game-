#ifndef SCALEDSPRITE__H
#define SCALEDSPRITE__H
#include <string>
#include "drawable.h"



class scaledSprite : public Drawable {
public:
  scaledSprite(const std::string&);
  scaledSprite(const scaledSprite&);
  virtual ~scaledSprite();
  scaledSprite& operator=(const scaledSprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { return image; }
  virtual const SDL_Surface* getSurface() const { 
    return image->getSurface();
  }
  int getScaledWidth()  const { return getScale()*image->getWidth();  } 
  int getScaledHeight() const { return getScale()*image->getHeight(); } 

   

private:
  const Image * image;
  protected:
  int worldWidth;
  int worldHeight;
Vector2f makeVelocity(int, int) const;
};
#endif


