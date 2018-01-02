#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "scaledSprite.h"
#include "multisprite.h"
#include "smartSprite.h"
#include "shootingSprite.h"
#include "twowaysprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "player.h"
#include "collisionStrategy.h"
class SpriteLess {
public:
  bool operator()(const Drawable* lhs, const Drawable* rhs) const {
    return lhs->getScale() < rhs->getScale();
  }
};


Engine::~Engine() { 
  delete player;
  for ( Drawable* sprite : sprites ) {
    delete sprite;
  }
 for ( Drawable* spri : sprit ) {
    delete spri;
  }
for ( Drawable* spri : snow ) {
    delete spri;
  }

  for ( CollisionStrategy* strategy : strategies ) {
    delete strategy;
  }
  std::cout << "Terminating program" << std::endl;

}

Engine::Engine() :
 hud( Hud::getInstance() ),
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  Grass("Grass", Gamedata::getInstance().getXmlInt("Grass/factor") ),
  Land("Land", Gamedata::getInstance().getXmlInt("Land/factor") ),
  Building("Building", Gamedata::getInstance().getXmlInt("Building/factor") ),
  //star("star", Gamedata::getInstance().getXmlInt("star/factor") ),
  moon("moon", Gamedata::getInstance().getXmlInt("moon/factor") ),
  tree("Tree", Gamedata::getInstance().getXmlInt("Tree/factor") ),
  ftree("Ftree", Gamedata::getInstance().getXmlInt("Ftree/factor") ),
  viewport( Viewport::getInstance() ),
   player(new ShootingSprite("Phoenixleft","Phoenixright")),
  sprites(),
  sprit(),
  snow(),
  strategies(),
  currentStrategy(0),
  collision(false),
  makeVideo( false ),
  poolhud(*player),
displayhud(0),
toogleGodmode(0),
count(0),
godMode(false),
shootingleft(false),
life(3),
sound()
{
 int n = Gamedata::getInstance().getXmlInt("numberOfStars");
  sprites.reserve(n);
 Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  for (int i = 0; i < n; ++i) {
    sprites.push_back( new SmartSprite("Birdright","Birdleft", pos, w, h) );

    w=w+550;
    h=h+50;
    player->attach( sprites[i] );
  }

  for (int i = 0; i < 50; ++i ) {
    auto* s = new scaledSprite("snowFlake");
    float scale = Gamedata::getInstance().getRandFloat(1,2);
    s->setScale(scale);
    snow.push_back(s);
  }
  std::vector<Drawable*>::iterator ptr = snow.begin();
  ++ptr;
  sort(ptr, snow.end(), SpriteLess());

  sprit.push_back(new MultiSprite("fire1"));
  sprit.push_back(new MultiSprite("fire6"));
  sprit.push_back(new MultiSprite("fire10"));
//wall.push_back(new Sprite("iceball"));
  
  //strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  //strategies.push_back( new MidPointCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
  
 
}



void Engine::draw() const {
 int fact=snow.size()/3;
  moon.draw();
 // star.draw();

  ftree.draw();
  for(unsigned int i=fact*2;i<snow.size();i++){
  snow[i]->draw();}
  tree.draw();
  for( int i=fact;i<fact*2;i++){
  snow[i]->draw();}
  Building.draw();
  
  for(int i=0;i<fact;i++){
  snow[i]->draw();}
  Land.draw();
  Grass.draw();
//for(auto* s : snow) s->draw();

  for ( const Drawable* sprite : sprites ) {
    sprite->draw();
  }
for ( const Drawable* spri : sprit ) {
    spri->draw();
  }

 SDL_Color color1 = {102,0,204,255};
SDL_Color color2 = {255,0,0,255};
std::stringstream strm;
  strm << sprites.size() << " Enemies Remaining";
  IOmod::getInstance().writeText(strm.str(),color2,30, 30);
if(godMode==true){
std::stringstream strm1;
strm1<<"God Mode: ON";
IOmod::getInstance().writeText(strm1.str(),color1,30, 420);
}
 
 if ( sprites.size() == 0 && life>0) {
     //IOmod::getInstance().writeText("Press R to Restart the game", 250, 400);
	hud.displayWin(count);
    clock.pause();
  }
if ( sprites.size() > 0 && life==0) {
    // IOmod::getInstance().writeText("Press R to Restart the game", 250, 400);
	hud.displayLost(count);
    clock.pause();
  }
 
  hud.printHealth(life);
  strategies[currentStrategy]->draw();
  if ( collision ) {
    //IOmod::getInstance().writeText("Oops: Collision", 500, 60);
  }
  player->draw();
unsigned int sec = Gamedata::getInstance().getXmlInt("hud/seconds");

  if(displayhud%2!=0 || clock.getSeconds()<sec){
	hud.displayHud(); }
	poolhud.draw();

   IOmod::getInstance().writeText("Sravani Chatrathi",color1,30,450);

//std::stringstream score;
   // score << "Score: " << count;
//IOmod::getInstance().writeText(score.str(),color1,30,380);
 	
std::stringstream lives;
    lives << "Remaining life: " << life;
//IOmod::getInstance().writeText(lives.str(),color1,30,410);

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  collision = false;
  for (  TwoWayEnemySprite* d : sprites ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
}
  }
for ( const Drawable* d : sprit ) {
    if ( strategies[currentStrategy]->execute(*player, *d) ) {
      collision = true;
    }
  }
  if ( collision ) {
    player->collided();
  }
  else {
    player->missed();
    collision = false;
  }

auto it = sprites.begin();
  while ( it != sprites.end() ) {
    if ( strategies[currentStrategy]->execute(*player, **it)) {
	count++; sound[5];
	if(!godMode){
	player->explode();
	}
	
	(*it)->explode();
		(*it)->setPosition(Vector2f((*it)->getPosition()[0] + 2500 , (*it)->getPosition()[1]));	
			
		it++; 
	if(!godMode){life--; }
		
          }
	else if((player)->collidedB((*it))){
	count++;
        sound[3];
	(*it)->explode();
	
	(*it)->setPosition(Vector2f((*it)->getPosition()[0] + 2500 , (*it)->getPosition()[1]));
         it++;
	
	}
	else ++it;
	}
	
	
	
	it = sprites.begin();
  while ( it != sprites.end() ) {
    if ( (*it)->deleteenemy() ) {
      SmartSprite* doa = *it;
      player->detach(doa);
      delete doa;
      it = sprites.erase(it);
	//it++;
    }
    else ++it;
  }
	
auto it1 = sprit.begin();
  while ( it1 != sprit.end() ) {
    if ( strategies[currentStrategy]->execute(*player, **it1) ) {
     count++;sound[10];
      it1 = sprit.erase(it1);
	
    }
    else ++it1;
  }




}


void Engine::update(Uint32 ticks) {

 checkForCollisions();
  player->update(ticks);

  for ( Drawable* sprite : sprites ) {
    sprite->update( ticks );
  }
for ( Drawable* sprite : sprit ) {
    sprite->update( ticks );
  }
 for(auto* s : snow) s->update(ticks);

  moon.update();
  //star.update();
  ftree.update();
  tree.update();
  Building.update();
  Land.update();
  Grass.update();

	

	

  viewport.update(); // always update viewport last
}


bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

 while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_M] ) {
          currentStrategy = (1 + currentStrategy) % strategies.size();
        }
	
	 if ( keystate[SDL_SCANCODE_R] ) {
          clock.unpause();
	  godMode=false;
          return true;

        }
	
     if (keystate[SDL_SCANCODE_F1]) {
     ++displayhud;

	}
if ( keystate[SDL_SCANCODE_SPACE]) {
			
            if(shootingleft==true){ player->shootleft(); sound[8]; }
		else{	
            player->shoot(); sound[8];
		}
           
           
		}
	
	if ( keystate[SDL_SCANCODE_G]) {
	++toogleGodmode;
	if(toogleGodmode%2!=0){godMode=true;}
	else {godMode=false;}
	}
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }
    // In this section of the event loop we allow key bounce:

     // In this section of the event loop we allow key bounce:
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
     

      if (keystate[SDL_SCANCODE_A]) {
        player->left();
       shootingleft=true;
	
      }
      if (keystate[SDL_SCANCODE_D]) {
        player->right();
	shootingleft=false;
      }
      if (keystate[SDL_SCANCODE_W]) {
        player->up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        player->down();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
 return false;
}
