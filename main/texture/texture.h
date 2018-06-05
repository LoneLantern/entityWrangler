#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include "../utility/application.h"
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include "../data/geometric.h"
#include "../utility/instanceCounted.h"
#include "../component/component.h"

void save_texture(SDL_Renderer *ren, SDL_Texture *tex, const char *filename);
class Texture:InstanceCounted<Texture>,public Base
{
private:
    bool openForChanges = false;
    static const uint32_t R_MASK;
    static const uint32_t G_MASK;
    static const uint32_t B_MASK;
    static const uint32_t A_MASK;
    static Texture nullTex;
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

    void setOpenForChanges(bool state){
        this->openForChanges = state;
        if(state==false){
            this->initFromSDLSurf(this->SDLSurf);
//            std::cout<<"Closed texture...\n";
        }
    }

    bool isOpenForChanges(){
        return this->openForChanges;
    }

    Texture(const char* file);
    Texture()
    {
        this->initFromFile("./error.png");

    }
    Texture(SDL_Surface *surface);

    virtual SDL_Texture *use(GLenum channel = GL_TEXTURE0) ;
    void copyOnto(const Texture& rhs, SYSTEM_NAMESPACE::Vec2i location, bool changeSize = false, bool leaveOpenForChanges = false)
    {
        this->setOpenForChanges(true);
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
        SDL_Rect originalDim = {
            0,0,this->SDLSurf->w,this->SDLSurf->h
        };
        SDL_Rect otherDim = {
            location.x,location.y,wrhs,hrhs
        };

        SDL_LockSurface(this->SDLSurf);
        SDL_Surface *newSurf = SDL_CreateRGBSurface(0,w,h,32,R_MASK,G_MASK,B_MASK,A_MASK);
        SDL_SetSurfaceBlendMode(newSurf,SDL_BLENDMODE_NONE);

        SDL_UnlockSurface(this->SDLSurf);
        SDL_BlitSurface(this->SDLSurf,NULL,newSurf,&originalDim);

        SDL_BlitSurface(rhs.SDLSurf,NULL,newSurf,&otherDim);
//        std::cout<<"initializing blitted texture\n";
        SDL_FreeSurface(this->SDLSurf);
        this->SDLSurf = newSurf;

        if(leaveOpenForChanges==true){
            return;
        }
        this->setOpenForChanges(false);
    }
    SYSTEM_NAMESPACE::Vec2f getGLCDimensions();
    virtual SYSTEM_NAMESPACE::Vec2i getPxDimensions();
    virtual SYSTEM_NAMESPACE::Vec2i getPxDimensions(SYSTEM_NAMESPACE::Vec3f scale);

    virtual ~Texture();

};
namespace component
{
typedef Component<Texture> textureComponents;
}
#endif // TEXTURE_H_INCLUDED
