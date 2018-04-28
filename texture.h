#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include "application.h"
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include "window.h"
#include "geometric.h"
#include "instanceCounted.h"
#include "component.h"

void save_texture(SDL_Renderer *ren, SDL_Texture *tex, const char *filename);
class Texture:InstanceCounted<Texture>,public Base
{
private:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    const uint32_t R_MASK = 0xff000000;
    const uint32_t G_MASK = 0x00ff0000;
    const uint32_t B_MASK = 0x0000ff00;
    const uint32_t A_MASK = 0x000000ff;
#else
    const uint32_t R_MASK = 0x000000ff;
    const uint32_t G_MASK = 0x0000ff00;
    const uint32_t B_MASK = 0x00ff0000;
    const uint32_t A_MASK = 0xff000000;
#endif
    SDL_Texture *SDLTex;
    SDL_Surface *SDLSurf;
    GLuint GLTex;
    SYSTEM_NAMESPACE::Vec2f dimensions;

    virtual void initSDLImg();
    virtual void initDimensions(SDL_Surface *surface);
    virtual void initFromSDLSurf(SDL_Surface *surface);
    virtual void initFromFile(const char* file);

public:
    static GLuint SDLSurf2GLTex(SDL_Surface *texture);
    static SDL_Surface surfaceFromData(std::string data);
    Texture(const char* file);
    Texture()
    {
        this->initFromFile("./error.png");

    }
    Texture(SDL_Surface *surface);

    virtual SDL_Texture *use(GLenum channel = GL_TEXTURE0);
    void copyOnto(const Texture& rhs, Vec2i location, bool changeSize = false)
    {
        uint32_t format;
        int ac;
        int w;
        int h;
        int wrhs;
        int hrhs;

        SDL_QueryTexture(this->SDLTex,&format,&ac,&w,&h);
        SDL_QueryTexture(rhs.SDLTex,NULL,NULL,&wrhs,&hrhs);

        if(changeSize == true)
        {
            w+=wrhs-(w-location.x);
            h+=hrhs-(h-location.y);
        }
        SDL_LockSurface(this->SDLSurf);
        SDL_Surface *newSurf = SDL_CreateRGBSurface(0,w,h,32,R_MASK,G_MASK,B_MASK,A_MASK);

        SDL_UnlockSurface(this->SDLSurf);

        SDL_BlitSurface(this->SDLSurf,NULL,newSurf,&((SDL_Rect)
        {
            0,0,this->SDLSurf->w,this->SDLSurf->h
        }));

        SDL_BlitSurface(rhs.SDLSurf,NULL,newSurf,&((SDL_Rect)
        {
            location.x,location.y,wrhs,hrhs
        }));
        std::cout<<"initializing blitted texture\n";
        this->initFromSDLSurf(newSurf);

    }
    Vec2f getGLCDimensions();
    virtual Vec2i getPxDimensions();
    virtual Vec2i getPxDimensions(Vec3f scale);

    virtual ~Texture();

};
namespace component
{
typedef Component<Texture> textureComponents;
}
#endif // TEXTURE_H_INCLUDED
