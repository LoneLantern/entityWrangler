#ifndef RENDERERSDL_H_INCLUDED
#define RENDERERSDL_H_INCLUDED
#include "renderer.h"
#include <iostream>


class RendererSDL:public Renderer{
private:
    SDL_Renderer *sdlRenderer;
    SDL_Color color;
    float strokeWidth;
public:
    RendererSDL();
    virtual void drawText( const char* text);
    virtual void drawRectangle(const SYSTEM_NAMESPACE::Rectangle &rect, bool filled = false);
    virtual void drawCircle(float x, float y,float radius, bool filled= false);
    virtual void drawLine(const SYSTEM_NAMESPACE::Vec3f pointA, const SYSTEM_NAMESPACE::Vec3f pointB);
    virtual void drawTexture(const Texture &texture, const SYSTEM_NAMESPACE::Rectangle &rect, float rotation = 0.0f, SYSTEM_NAMESPACE::Vec2f center = {0.0f,0.0f});
    virtual void setColor(float r, float g,float b,float a = 1.0f);
    virtual void setStrokeWidth(float width);
    virtual void show();

};

#endif // RENDERERSDL_H_INCLUDED
