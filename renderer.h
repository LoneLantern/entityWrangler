#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED
#include "font.h"
#include "geometric.h"
#include "texture.h"

class Renderer{
public:
    virtual void drawText( const char* text) = 0;
    virtual void drawRectangle(const SYSTEM_NAMESPACE::Rectangle &rect, bool filled = false) = 0;
    virtual void drawRectangle(float x,float y,float z,float h,float w, bool filled = false){
        this->drawRectangle({x,y,z,h,w},filled);
    }

    virtual void drawCircle(float x, float y,float radius, bool filled= false) = 0;
    virtual void drawLine(const SYSTEM_NAMESPACE::Vec3f pointA, const SYSTEM_NAMESPACE::Vec3f pointB) = 0;
    virtual void drawLine(float aX, float aY, float aZ, float bX, float bY, float bZ){
        this->drawLine({aX,aY,aZ},{bX,bY,bZ});
    };
    virtual void drawTexture(const Texture &texture, const SYSTEM_NAMESPACE::Rectangle &rect, float rotation = 0.0f, SYSTEM_NAMESPACE::Vec2f center = {0.0f,0.0f});
    virtual void setColor(float r, float g,float b,float a = 1.0f) = 0;
    virtual void setStrokeWidth(float width) = 0;
    virtual void show() = 0;
};

#endif // RENDERER_H_INCLUDED
