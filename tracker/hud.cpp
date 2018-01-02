#include "hud.h"
#include "ioMod.h"
#include "clock.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include <sstream>
Hud& Hud::getInstance(){
    static Hud instance;
    return instance;
}

Hud::Hud():
    
    width(Gamedata::getInstance().getXmlInt("hud/width")),
    height(Gamedata::getInstance().getXmlInt("hud/height")),
    x(Gamedata::getInstance().getXmlInt("hud/start/x")),
    y(Gamedata::getInstance().getXmlInt("hud/start/y")),
    Rectangle({x,y,width,height}),
    renderer( RenderContext::getInstance()->getRenderer() )
   {}

Hud::~Hud()
{}

void Hud::displayLost(int count) const{
    SDL_Rect Rectl = {300,330,200,120};
    SDL_Color Textcolor = {255,0,0,255};
    std::stringstream str1;
    str1 << "You LOST!";
    std::stringstream str4;
    str4 << "Your Score: "<<count;
    std::stringstream str2;
    str2 << "Game Over";
    std::stringstream str3;
    str3 << "Press R to Restart";
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &Rectl );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &Rectl );
    IOmod::getInstance().writeText(str1.str(), Textcolor,320+15, 330+15);
    IOmod::getInstance().writeText(str4.str(), Textcolor,320+15, 330+40);
    IOmod::getInstance().writeText(str2.str(),  Textcolor,320+15, 330+65);
    IOmod::getInstance().writeText(str3.str(),  Textcolor,302, 330+90);
}

void Hud::displayWin(int count) const{
    SDL_Rect RectW = {300,330,200,120};
    SDL_Color Textcolor = {255,0,0,255};
    std::stringstream str1;
    str1 << "You WON!";
   std::stringstream str4;
    str4 << "Your Score: "<<count;
    std::stringstream str2;
    str2 << "Game Over";
    std::stringstream str3;
    str3 << "Press R to Restart";
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &RectW );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &RectW );
    IOmod::getInstance().writeText(str1.str(), Textcolor,320+15, 330+15);
    IOmod::getInstance().writeText(str4.str(), Textcolor,320+15, 330+40);
    IOmod::getInstance().writeText(str2.str(),  Textcolor,320+15, 330+65);
    IOmod::getInstance().writeText(str3.str(),  Textcolor,302, 330+90);
}

void Hud::displayHud() const{
    std::stringstream fps;
    fps << "Fps: " << Clock::getInstance().getFps();
    std::stringstream seconds; 
    seconds<< "Elapsed seconds: "<<Clock::getInstance().getSeconds();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &Rectangle );
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderDrawRect( renderer, &Rectangle );
    SDL_Color Textcolor = {102,0,51,255};
   //IOmod::getInstance().writeText("Take sparkling fire ",Textcolor, x+15, y+5);
   //IOmod::getInstance().writeText("For Extra lives ",Textcolor, x+18, y+25);
    IOmod::getInstance().writeText(fps.str(), Textcolor,x+15, y+10);
    IOmod::getInstance().writeText(seconds.str(),Textcolor, x+15, y+35);
    IOmod::getInstance().writeText("Press these ",Textcolor, x+15, y+60);
    IOmod::getInstance().writeText("a: Left ",Textcolor, x+15, y+85);
    IOmod::getInstance().writeText("d: Right",Textcolor, x+15, y+110);
    IOmod::getInstance().writeText("w: Up",Textcolor, x+15, y+135);
    IOmod::getInstance().writeText("s: Down",Textcolor, x+15, y+160);
    IOmod::getInstance().writeText("space: Shoot",Textcolor, x+15, y+185);
    IOmod::getInstance().writeText("G: God Mode",Textcolor, x+15, y+210);
    IOmod::getInstance().writeText("F1: Help",Textcolor, x+15, y+235);
     IOmod::getInstance().writeText("P: Pause",Textcolor, x+15, y+260);
  
  }



void Hud::printHealth(int lives) const{
/*if(godMode==true){
 SDL_Rect RectW = {30,60,180,20};
 SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderFillRect( renderer, &RectW );
   // SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
   // SDL_RenderDrawRect( renderer, &RectW );
}
else
{*/
SDL_Rect RectW = {30,60,180,20};
 SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255);
    SDL_RenderFillRect( renderer, &RectW );
    if(lives<3){
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);
    SDL_RenderFillRect( renderer, &RectW );
    int p= (180*lives)/3;
    SDL_Rect Rectx={30,60,p,20};
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderFillRect(renderer,&Rectx);
    }
    //SDL_RenderDrawRect( renderer, &RectW );
}
//}
