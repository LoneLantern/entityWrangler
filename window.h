#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <GL/glew.h>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdexcept>
#include "geometric.h"
#include "renderer.h"

#define SDL_MAIN int main(int argc, char *argv[])
#define SDL_MAIN_PARAM int argc, char *argv[]
using namespace SYSTEM_NAMESPACE;

class Window
{
private:
    Renderer *renderer;
    SDL_Window *window;
    SDL_GLContext context;
    SDL_Rect dimensions;

    static Window *activeWindow;
    static Renderer *activeRenderer;

    void initDimensions(int x,int y,int w,int h);

    void initWindow(const char* name,int x,int y,int w,int h,int FLAGS);

public:

    static void initSystems();

    static void initOGLSystems();

    Window(const char* name,int x,int y,int w,int h,int FLAGS);

    SDL_Window *getWindow();

    Renderer *getRenderer();

    SDL_GLContext getContext();

    void makeActive();

    explicit operator SDL_Window* ()
    {
        return this->window;
    };
    explicit operator Renderer* ()
    {
        return this->renderer;
    };

    void swap();
    //DO NOT USE WINDOW FUNCTIONS TO CONVERT A PIXEL TO A COORDINATE THAT REQUIRES PERSPECTIVE!!
    static Vec2f px2GLC(Vec2i px);
    static Vec2i gLC2Px(Vec2f gLC);

    static Window &getActiveWindow();

    static Renderer *getActiveRenderer();
    SDL_Rect getDimensions();
    ~Window();

};

#endif // WINDOW_H_INCLUDED
