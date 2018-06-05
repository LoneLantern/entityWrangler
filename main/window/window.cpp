#include "window.h"
#include <iostream>
#include <math.h>
#include "../renderer/renderer.h"
#include "../renderer/rendererSDL.h"

using namespace std;
Window*     Window::activeWindow    =   nullptr;
Renderer* Window::activeRenderer = nullptr;


Vec2f Window::px2GLC(Vec2i px)
{
    return {((float)px.x/(float)Window::activeWindow->dimensions.w)*2.0f-1.0f,
            ((float)px.y/(float)Window::activeWindow->dimensions.h)*2.0f-1.0f};
}

Vec2i Window::gLC2Px(Vec2f GLc)
{
    return {lround(((GLc.x+1.0f)/2.0f)*Window::activeWindow->dimensions.w),
            lround(((GLc.y+1.0f)/2.0f)*Window::activeWindow->dimensions.h)};
}


void Window::initSystems()
{
    if(SDL_WasInit(SDL_INIT_VIDEO)&&SDL_Init(SDL_INIT_VIDEO)==-1)
    {
        throw std::runtime_error("SDL_Video_Init Err");
    }
}

void Window::initOGLSystems()
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        throw std::runtime_error((const char*)glewGetErrorString(err));
    }
}

void Window::initWindow(const char* name,int x,int y,int w,int h,Renderer* renderer,int flags)
{
    this->initSystems();
    this->initDimensions(x,y,w,h);
    this->window = SDL_CreateWindow(name,x,y,w,h,flags);
    if(!this->window)
    {
        throw std::runtime_error(SDL_GetError());
    }
    if(flags&SDL_WINDOW_OPENGL)
    {
        SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
        SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3); //OpenGL 3+
        SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 2); //OpenGL 3.3
        if((this->context = SDL_GL_CreateContext(this->window))==NULL)
        {
            throw std::runtime_error(SDL_GetError());
        }
        this->renderer = nullptr;
        this->initOGLSystems();
    }
    else
    {
        this->sdlRenderer = SDL_CreateRenderer(this->window,-1,SDL_RENDERER_ACCELERATED);
       // if(renderer == NULL||renderer == nullptr)
            renderer = new RendererSDL(this->sdlRenderer);
        this->renderer = renderer;
        if(!this->renderer)
            throw std::runtime_error(SDL_GetError());
    }

    if(Window::activeWindow     ==  nullptr)
    {
        Window::activeWindow    =   this;
    }

    if(Window::activeRenderer   ==  nullptr)
    {
        Window::activeRenderer  = this->renderer;
    }

}


void Window::initDimensions(int x,int y,int w,int h)
{
    this->dimensions = {x,y,w,h};
}

SDL_Rect Window::getDimensions()
{
    return this->dimensions;
}

SDL_Renderer *Window::getSDLRenderer(){
    return this->sdlRenderer;
}

Window::Window(const char* name,int x,int y,int w,int h,int flags)
{
    this->initWindow(name,x,y,w,h,NULL,flags);
}

Window::Window(const char* name,int x,int y,int w,int h,Renderer *renderer,int flags)
{

    this->initWindow(name,x,y,w,h,renderer,flags);
}

SDL_Window *Window::getWindow()
{
    return this->window;
}

Renderer *Window::getRenderer()
{
    /*if(this->renderer==nullptr)
    {
        throw std::runtime_error("Tried to get renderer when mode is opengl");
    }*/
    return this->renderer;
}

SDL_GLContext Window::getContext()
{
    return this->context;
}

void Window::makeActive()
{
    Window::activeWindow = this;
    Window::activeRenderer = this->renderer;
}

Window &Window::getActiveWindow()
{
    return *Window::activeWindow;
}

Renderer *Window::getActiveRenderer()
{
    return Window::activeRenderer;
}


void Window::swap()
{
    this->renderer->show();
}




Window::~Window()
{
    if(this==Window::activeWindow)
    {
        Window::activeWindow = nullptr;
        Window::activeRenderer = nullptr;
    }

    SDL_DestroyWindow(this->window);
    if(this->renderer!=nullptr)
        SDL_DestroyRenderer(this->sdlRenderer);
    else SDL_GL_DeleteContext(this->context);

}
