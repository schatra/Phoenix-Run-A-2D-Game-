#include <cmath>
#include <random>
#include <functional>
#include "scaledSprite.h"
#include "gamedata.h"
#include "renderContext.h"


Vector2f scaledSprite::makeVelocity(int vx, int vy) const {
  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();

  return Vector2f(newvx, newvy);
}

scaledSprite::~scaledSprite() {  } 



scaledSprite::scaledSprite(const std::string& name):
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
		Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           makeVelocity(
                    Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")) 
           ),
  image( RenderContext::getInstance()->getImage(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ 
	setPosition(Vector2f(rand()%(worldWidth-1000)+500, rand()%(worldHeight-500)+500));
}

scaledSprite::scaledSprite(const scaledSprite& s) :
  Drawable(s), 
  image(s.image),
  
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

scaledSprite& scaledSprite::operator=(const scaledSprite& rhs) {
  Drawable::operator=( rhs );
  image = rhs.image;
 
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}



void scaledSprite::draw() const { 
  if(getScale() < SCALE_EPSILON) return;
   image->draw(getX(), getY(), getScale()); 
}

void scaledSprite::update(Uint32 ticks) { 
 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( std::abs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -std::abs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( std::abs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -std::abs( getVelocityX() ) );
  }  
}
