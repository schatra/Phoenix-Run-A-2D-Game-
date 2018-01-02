#include "shootingSprite.h"
#include "gamedata.h"
#include "imageFactory.h"

ShootingSprite::ShootingSprite(const std::string& right,const std::string& left) :
  Player(right,left),
  bulletName( Gamedata::getInstance().getXmlStr(left+"/bullet") ),
  bullets(bulletName),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  timeSinceLastFrame(0)

{ }

ShootingSprite::ShootingSprite(const ShootingSprite& s) :
  Player(s),
  bulletName(s.bulletName),
  bullets(s.bullets),
  minSpeed(s.minSpeed),
  bulletInterval(s.bulletInterval),
  timeSinceLastFrame(s.timeSinceLastFrame)


{ }

void ShootingSprite::shoot() { 
 
  if ( timeSinceLastFrame < bulletInterval ) return;
  float deltaX = getScaledWidth();
  float deltaY = getScaledHeight()/2;
  // I need to add some minSpeed to velocity:
  
  Bullet bullet(bulletName);
  bullets.shoot( getPosition() +Vector2f(deltaX, deltaY) , getVelocity() + Vector2f(minSpeed, 0));
  timeSinceLastFrame = 0;
}

void ShootingSprite::shootleft() { 
 
  if ( timeSinceLastFrame < bulletInterval ) return;
  float deltaX = getScaledWidth()-150;
  float deltaY = getScaledHeight()/2;
  // I need to add some minSpeed to velocity:
  
  Bullet bullet(bulletName);
  bullets.shoot( getPosition() +Vector2f(deltaX, deltaY) , getVelocity() - Vector2f(minSpeed, 0));
  timeSinceLastFrame = 0;
}

bool ShootingSprite::collidedB(const Drawable* obj) const { 
  //std::list<Bullet>::iterator ptr = bulletList.begin(); 
 return bullets.collided( obj );
  
}

void ShootingSprite::draw() const { 
  Player::draw();
    bullets.draw();
}

void ShootingSprite::update(Uint32 ticks) { 
	timeSinceLastFrame += ticks;
        Player::update(ticks);
       bullets.update(ticks);

}

