#include "rendererSDL.h"
#include "../window/window.h"

#define SDL_RENDERDRAWRECT(renderer, rect, filled) SDL_Rect converted = rect; if(filled) SDL_RenderFillRect(renderer,&converted); else SDL_RenderDrawRect(renderer,&converted);
#define SDK_RENDERDRAWCIRCLE(renderer, x, y, radius, filled) if(filled) filledCircleRGBA (renderer,x,y,radius,this->color.r,this->color.g,this->color.b,this->color.a); else circleRGBA(renderer,x,y,radius,this->color.r,this->color.g,this->color.b,this->color.a);
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
    //thickLineRGBA(this->sdlRenderer, Window::gLC2Px({pointA.x,0.0f}).x, Window::gLC2Px({pointA.y,0.0f}).x, Window::gLC2Px({pointB.x,0.0f}).x, Window::gLC2Px({pointB.y,0.0f}).x, this->strokeWidth, this->color.r, this->color.b, this->color.g, this->color.a);
    SDL_RenderDrawLine(this->sdlRenderer,Window::gLC2Px({pointA.x,0.0f}).x, Window::gLC2Px({pointA.y,0.0f}).x, Window::gLC2Px({pointB.x,0.0f}).x, Window::gLC2Px({pointB.y,0.0f}).x);
}

void RendererSDL::drawTexture(Texture &texture, const SYSTEM_NAMESPACE::Rectangle &rect, float rotation, Vec2f center){
    SDL_Rect converted = rect;
    SDL_Point centerConverted = {center.x,center.y};
    SDL_RenderCopyEx(this->sdlRenderer, texture.use(), NULL, &converted,rotation,&centerConverted,SDL_FLIP_NONE);
}

void RendererSDL::setColor(float r, float g,float b, float a){
    this->color.r = r*255;
    this->color.g = g*255;
    this->color.b = b*255;
    this->color.a = a*255;

}

void RendererSDL::setStrokeWidth(float width){
    this->strokeWidth = width;
}

void RendererSDL::show(){
    SDL_RenderPresent(this->sdlRenderer);
}

