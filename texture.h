#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include "application.h"
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include "window.h"
#include "types.h"
#include "instanceCounted.h"
#include "component.h"

void save_texture(SDL_Renderer *ren, SDL_Texture *tex, const char *filename);
class Texture:InstanceCounted<Texture>,public Base
{
private:
    SDL_Texture *SDLTex;
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
    Texture(){
        this->initFromFile("./error.png");
    }
    Texture(SDL_Surface *surface);

    virtual SDL_Texture *use(GLenum channel = GL_TEXTURE0);

    Vec2f getGLCDimensions();
    Vec2i getPxDimensions();
    Vec2i getPxDimensions(Vec3f scale);

    virtual ~Texture();

};
namespace component{
    typedef Component<Texture> textureCT;
}
#endif // TEXTURE_H_INCLUDED
