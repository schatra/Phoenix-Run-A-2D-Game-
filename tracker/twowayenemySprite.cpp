
#include "gamedata.h"
#include "renderContext.h"
#include "twowayenemySprite.h"
#include "explodingSprite.h"

Vector2f TwoWayEnemySprite::makeVelocity(int vx, int vy) const {
  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();

  return Vector2f(newvx, newvy);
}

void TwoWayEnemySprite::advanceFrame(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
    timeSinceLastFrame = 0;
  }
}

TwoWayEnemySprite::~TwoWayEnemySprite( ) { if (explosion) delete explosion; }



TwoWayEnemySprite::TwoWayEnemySprite(const std::string& left, const std::string& right) :
  Drawable(left, 
           Vector2f(Gamedata::getInstance().getXmlInt(left+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(left+"/startLoc/y")), 
           makeVelocity(Gamedata::getInstance().getXmlInt(left+"/speedX"),
                    Gamedata::getInstance().getXmlInt(left+"/speedY"))
           ),
  images( RenderContext::getInstance()->getImages(left) ),
 explosion(nullptr),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(left+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(left+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  rightsprite(right),
  leftsprite(left),
deletesprite(false)
{ }

TwoWayEnemySprite::TwoWayEnemySprite(const TwoWayEnemySprite& s) :
  Drawable(s), 
  images(s.images),
   explosion(s.explosion),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  rightsprite(s.rightsprite),
  leftsprite(s.leftsprite),
deletesprite(s.deletesprite)
  { }

TwoWayEnemySprite& TwoWayEnemySprite::operator=(const TwoWayEnemySprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  explosion = (s.explosion);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  rightsprite = (s.rightsprite);
  leftsprite = (s.leftsprite);
deletesprite=(s.deletesprite);
  return *this;
}

void TwoWayEnemySprite::explode() {
  if ( !explosion ) {
explosion = new ExplodingSprite(Sprite(getName(), getPosition(), getVelocity(), images[currentFrame]));

  }

}

void TwoWayEnemySprite::draw() const { 
 if ( explosion ) explosion->draw();
 else images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWayEnemySprite::reset() {
setPosition(Vector2f(4500,140));
}

void TwoWayEnemySprite::update(Uint32 ticks) { 

  if ( explosion &&explosion->chunkCount()>0)  {
  
    explosion->update(ticks);
	return;
}
 else if ( explosion && explosion->chunkCount() == 0 ){
      delete explosion;
      explosion = NULL;
	deletesprite=true;
	//reset();
	
   return;
  }


  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
    setName(rightsprite);
    Images_set( RenderContext::getInstance()->getImages(rightsprite) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
    setName(leftsprite);
    Images_set( RenderContext::getInstance()->getImages(leftsprite) );
  }  

}
