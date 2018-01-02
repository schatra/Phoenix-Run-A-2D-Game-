#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "smartSprite.h"
#include "poolHud.h"
#include "bulletsPool.h"
#include "sound.h"

class ShootingSprite;
class CollisionStrategy;


class Engine {
public:
  Engine ();
  ~Engine ();
  bool play();
  //void switchSprite();
 Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
 

private:
   Hud& hud;
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World Grass;
  World Land;
  World Building;
  //World star;
  World moon;
  World tree;
  World ftree;
  Viewport& viewport;
  
 // int currentSprite;
  ShootingSprite* player;
  std::vector<SmartSprite*> sprites;
  std::vector<Drawable*> sprit;
  std::vector<Drawable*> snow;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  bool makeVideo;
  PoolHud poolhud;
  int displayhud;
  int toogleGodmode;
  int count;
bool godMode;
  bool shootingleft;
int life;
SDLSound sound;
  void draw() const;
  void update(Uint32);
//void delete1();
 // void printHealth() const;
  void checkForCollisions();
};
