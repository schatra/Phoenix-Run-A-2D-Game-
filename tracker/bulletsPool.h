#ifndef BULLETSPOOL_H
#define BULLETSPOOL_H

#include <list>
#include "bullet.h"

class CollisionStrategy; 

class BulletsPool {
public:
  BulletsPool(const std::string&);
  BulletsPool(const BulletsPool&);
  ~BulletsPool();
  void draw() const;
  void update(Uint32 ticks);
  void shoot(const Vector2f& pos, const Vector2f& vel);

  unsigned int bulletCount() const { return bulletList.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
  bool shooting() const { return !bulletList.empty(); }
  bool collided(const Drawable*) const;
private:
  std::string name;
  Vector2f myVelocity;
  mutable std::list<Bullet> bulletList; 
  mutable std::list<Bullet> freeList;   
  CollisionStrategy* strategy;
  BulletsPool& operator=(const BulletsPool&);   
};
#endif
