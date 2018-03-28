#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include <SDL/SDL.h>
#include <stdexcept>
#include <GL/glew.h>
#include <SDL/SDL_opengl.h>
#include <string>

class Base
{
public:
    virtual void initSystems(uint32_t flags);

    virtual void initOGLSystems();

};

#endif // APPLICATION_H_INCLUDED
