#include "player.h"
#include "renderContext.h"
#include "explodingSprite.h"


Player::~Player( ) { if (explosion) delete explosion; }
Player::Player( const std::string& right,const std::string& left) :
  TwoWaySprite(right,left),
  collision(false),

  initialVelocity(getVelocity()),
explosion(nullptr),
observers()
{ }

Player::Player(const Player& s) :
  TwoWaySprite(s), 
  collision(s.collision),

  initialVelocity(s.getVelocity()),
explosion(s.explosion),

 observers(s.observers)
  { }

Player& Player::operator=(const Player& s) {
  TwoWaySprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::explode(){
   // std::cout<<"helloo explode"<<std::endl;
        if(!explosion){
            explosion = new ExplodingSprite(Sprite(getName(), getPosition(), getVelocity(), images[currentFrame]));
		
    }
}

void Player::detach( SmartSprite* o ) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}


void Player::stop() { 
  setVelocity(Vector2f(0,0));
}

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
setName(rightsprite);
    Images_set( RenderContext::getInstance()->getImages(rightsprite) );
  }
} 
void Player::left()  { 
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
     setName(leftsprite);
      Images_set( RenderContext::getInstance()->getImages(leftsprite) );
   
  }
} 
void Player::up()    { 
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
} 
void Player::down()  { 
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::draw() const{
	
	if(explosion && explosion->chunkCount() != 0){
		explosion->draw();
    }
    else{
		TwoWaySprite::draw();
	}
}

void Player::reset()
{setPosition(Vector2f(50,140 ));

}
void Player::update(Uint32 ticks) {
//TwoWaySprite::update(ticks);
if ( explosion ) {
    explosion->update(ticks);
    if ( explosion->chunkCount() == 0 ) {
      delete explosion;
      explosion = NULL;
    }
    return;
  }
//TwoWaySprite::update(ticks);
  if ( !collision ) advanceFrame(ticks);
 Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;

 setPosition(getPosition() + incr); 
  stop();
 std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }
}




   

