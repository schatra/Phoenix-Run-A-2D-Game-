#ifndef PLAYER__H
#define PLAYER__H


#include "twowaysprite.h"
#include "smartSprite.h"
#include <list>
#include <cmath>
#include <string>
class ExplodingSprite;

class Player : public TwoWaySprite {
public:
  Player(const std::string&,const std::string&);
  Player(const Player&);
~Player();
virtual void draw() const;
  virtual void update(Uint32 ticks);


  void collided() { collision = true; }
  void missed() { collision = false; }
  
void reset();
  void right();
  void left();
  void up();
  void down();
  void stop();
 void Images_set(std::vector<Image *> Imagesnew) {
    images = Imagesnew;
  }
 void attach(SmartSprite* o) { observers.push_back(o); } 
  void detach(SmartSprite* o);
virtual void explode();
private:
  bool collision;

  Vector2f initialVelocity;
ExplodingSprite* explosion;
  Player& operator=(const Player&);
protected:
  std::list<SmartSprite*> observers;

};

#endif
