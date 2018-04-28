#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED
#include "geometric.h"
#include "component.h"
#include <SDL/SDL.h>
#include "window.h"
#include "application.h"
using namespace SYSTEM_NAMESPACE;

class Transform :public InstanceCounted<Transform>
{
private:
    Vec3f position;
    Vec3f rotation;
    Vec3f scale;
public:


    Transform(float x=0.0f, float y=0.0f,float z=0.0f,float xr=0.0f,float yr=0.0f,float zr=0.0f,float xs=1.0f,float ys=1.0f,float zs=1.0f)
    {
        this->position = {x,y,z};
        this->rotation = {xr,yr,zr};
        this->scale = {xs,ys,zs};
    }

    Vec3f getPosition()
    {
        return this->position;
    }
    Vec2f getPosition2D()
    {
        return (Vec2f)
        {
            this->position.x,this->position.y
        };
    }

    Vec3f getRotation()
    {
        return this->rotation;
    }
    Vec3f getScale()
    {
        return this->scale;
    }

    void setPosition(const Vec3f &position)
    {
        this->position = position;
    }
    void setRotation(const Vec3f &rotation)
    {
        this->rotation = rotation;
    }
    void setScale(const Vec3f &scale)
    {
        this->scale = scale;
    }
    SDL_Rect screenBound2D()
    {
        return {Window::gLC2Px({position.x,position.y}).x,Window::gLC2Px({position.x,position.y}).y,std::lround(this->scale.x),std::lround(this->scale.y)};
    }
    Rectangle screenBound2DF()
    {
        return {Window::gLC2Px({position.x,position.y}).x,Window::gLC2Px({position.x,position.y}).y,(this->scale.x),(this->scale.y)};
    }
};
namespace component
{
typedef Component<Transform> transformComponents;

}
#endif // TRANSFORM_H_INCLUDED
