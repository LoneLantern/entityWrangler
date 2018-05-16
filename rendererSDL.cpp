#include "rendererSDL.h"
#include "window.h"

#define SDL_RENDERDRAWRECT(renderer, rect, filled) SDL_Rect converted = rect; if(filled) SDL_RenderFillRect(renderer,&converted); else SDL_RenderDrawRect(renderer,&converted);
#define SDK_RENDERDRAWCIRCLE(renderer, x, y, radius, filled) if(filled) aacircleRGBA(renderer,x,y,radius,this->color.r,this->color.g,this->color.b,this->color.a); else filledCircleRGBA(renderer,x,y,radius,this->color.r,this->color.g,this->color.b,this->color.a);
#include <SDL/SDL2_gfxPrimitives.h>

RendererSDL::RendererSDL(SDL_Renderer *renderer){
    this->sdlRenderer = renderer;
    this->color.r = this->color.b = this->color.g = this->color.a = 255;
    this->strokeWidth = 1.0f;
}

void RendererSDL::drawText(const char* text){
    std::cout<<text<<"\n";
}

void RendererSDL::drawRectangle(const SYSTEM_NAMESPACE::Rectangle &rect, bool filled){
    SDL_RENDERDRAWRECT(this->sdlRenderer,rect,filled);
}
void RendererSDL::drawCircle(float x, float y,float radius, bool filled){
    SDK_RENDERDRAWCIRCLE(this->sdlRenderer,x,y,radius,filled);
}
void RendererSDL::drawLine(const SYSTEM_NAMESPACE::Vec3f pointA, const SYSTEM_NAMESPACE::Vec3f pointB){
    thickLineRGBA(this->sdlRenderer, pointA.x, pointA.y, pointB.x, pointB.y, this->strokeWidth, this->color.r, this->color.b, this->color.g, this->color.a);
}
void RendererSDL::drawTexture(Texture &texture, const SYSTEM_NAMESPACE::Rectangle &rect, float rotation, Vec2f center){
    SDL_Rect converted = rect;
    SDL_Point centerConverted = {center.x,center.y};
    SDL_RenderCopyEx(this->sdlRenderer, texture.use(), NULL, &converted,rotation,&centerConverted,SDL_FLIP_NONE);
}

void RendererSDL::setColor(float r, float g,float b,float a){
    this->color = {r,g,b,a};
}

void RendererSDL::setStrokeWidth(float width){
    this->strokeWidth = width;
}

void RendererSDL::show(){
    SDL_RenderPresent(this->sdlRenderer);
}

