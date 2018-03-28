#include "application.h"


void Base::initSystems(uint32_t flags)
{
    if(SDL_WasInit(flags)&&SDL_InitSubSystem(SDL_INIT_VIDEO)==-1)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

void Base::initOGLSystems()
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        throw std::runtime_error((const char*)glewGetErrorString(err));
    }
}
