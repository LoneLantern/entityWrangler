#include "texture.h"
///......Private
#include <iostream>




using namespace component;
using namespace std;

void save_texture(SDL_Renderer *ren, SDL_Texture *tex, const char *filename)
{
    SDL_Texture *ren_tex;
    SDL_Surface *surf;
    int st;
    int w;
    int h;
    int format;
    void *pixels;

    pixels  = NULL;
    surf    = NULL;
    ren_tex = NULL;
    format  = SDL_PIXELFORMAT_RGBA32;

    /* Get information about texture we want to save */
    st = SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    if (st != 0) {
        SDL_Log("Failed querying texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    ren_tex = SDL_CreateTexture(ren, format, SDL_TEXTUREACCESS_TARGET, w, h);
    if (!ren_tex) {
        SDL_Log("Failed creating render texture: %s\n", SDL_GetError());
        goto cleanup;
    }

    /*
     * Initialize our canvas, then copy texture to a target whose pixel data we
     * can access
     */
    st = SDL_SetRenderTarget(ren, ren_tex);
    if (st != 0) {
        SDL_Log("Failed setting render target: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(ren);

    st = SDL_RenderCopy(ren, tex, NULL, NULL);
    if (st != 0) {
        SDL_Log("Failed copying texture data: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Create buffer to hold texture data and load it */
    pixels = malloc(w * h * SDL_BYTESPERPIXEL(format));
    if (!pixels) {
        SDL_Log("Failed allocating memory\n");
        goto cleanup;
    }

    st = SDL_RenderReadPixels(ren, NULL, format, pixels, w * SDL_BYTESPERPIXEL(format));
    if (st != 0) {
        SDL_Log("Failed reading pixel data: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Copy pixel data over to surface */
    surf = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, SDL_BITSPERPIXEL(format), w * SDL_BYTESPERPIXEL(format), format);
    if (!surf) {
        SDL_Log("Failed creating new surface: %s\n", SDL_GetError());
        goto cleanup;
    }

    /* Save result to an image */
    st = SDL_SaveBMP(surf, filename);
    if (st != 0) {
        SDL_Log("Failed saving image: %s\n", SDL_GetError());
        goto cleanup;
    }

    SDL_Log("Saved texture as BMP to \"%s\"\n", filename);
cleanup:
    SDL_FreeSurface(surf);
    free(pixels);
    SDL_DestroyTexture(ren_tex);
}
void Texture::initSDLImg()
{
    int16_t flags = IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF;
    if(IMG_Init(0)==0&&IMG_Init(flags)!=flags)
    {
        throw std::runtime_error(IMG_GetError());
    }
}
void Texture::initFromSDLSurf(SDL_Surface *surface)
{
<<<<<<< HEAD
    this->initDimensions(surface);
=======
    std::cout<<"("<<surface->w<<"|"<<surface->h<<"|"<<surface->pitch/surface->w<<")\n";
    this->SDLSurf = surface;
    std::cout<<"("<<surface->w<<"|"<<surface->h<<"|"<<surface->pitch/surface->w<<")\n";
    this->initDimensions(surface);
    std::cout<<"("<<surface->w<<"|"<<surface->h<<"|"<<surface->pitch/surface->w<<")\n";

>>>>>>> Improved entity system. Some basic cleanup. Physics test
    if(Window::getActiveRenderer()!=nullptr&&Window::getActiveRenderer()!=NULL)
    {
        this->SDLTex = SDL_CreateTextureFromSurface(Window::getActiveRenderer(),surface);
        if(!this->SDLTex)
        {
            throw std::runtime_error(IMG_GetError());
        }

    }
    else this->SDLTex = nullptr;
<<<<<<< HEAD
    this->GLTex = this->SDLSurf2GLTex(surface);
=======
    std::cout<<"("<<surface->w<<"|"<<surface->h<<"|"<<surface->pitch/surface->w<<")\n";
    this->GLTex = this->SDLSurf2GLTex(surface);
    std::cout<<"("<<surface->w<<"|"<<surface->h<<"|"<<surface->pitch/surface->w<<")\n";

>>>>>>> Improved entity system. Some basic cleanup. Physics test
//     this->width = Window::px2GLC(surface->w);
     //this->height = Window::getActiveWindow()->px2GLC(surface->h);

}



void Texture::initDimensions(SDL_Surface *surface)
{
<<<<<<< HEAD
    this->dimensions.x = Window::px2GLC({surface->w,0}).x;
    this->dimensions.y = Window::px2GLC({0,surface->h}).y;
=======
    cout<<"tex:" <<surface->w<<" | "<<surface->h<<" \n";
    this->dimensions.x = Window::px2GLC({surface->w,0}).x;
    this->dimensions.y = Window::px2GLC({0,surface->h}).y;

>>>>>>> Improved entity system. Some basic cleanup. Physics test
}

void Texture::initFromFile(const char* file)
{
    this->initSDLImg();
    /*std::string data = File::request(file);
    SDL_Surface *surf = IMG:*/
    SDL_Surface *surf = IMG_Load(file);
    if(!surf)
    {
        throw std::runtime_error(SDL_GetError());
    }
    //this->initDimensions(surf);
    this->initFromSDLSurf(IMG_Load(file));
}



GLuint Texture::SDLSurf2GLTex(SDL_Surface *surf)
{
    GLuint TextureID = 0;

    glGenTextures(1,&TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    int Mode = GL_RGB;

    if(surf->format->BytesPerPixel == 4)
    {
        Mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, Mode, surf->w, surf->h, 0, Mode, GL_UNSIGNED_BYTE, surf->pixels);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);
    return TextureID;
}


///******Public
Texture::Texture(const char* file)
{
    std::cout<<"Constructing new"<<"\n";
    this->initSystems(SDL_INIT_VIDEO);
    initFromFile(file);
}

Texture::Texture(SDL_Surface *texture)
{
    this->initSystems(SDL_INIT_VIDEO);
    this->initFromSDLSurf(texture);
}



SDL_Texture* Texture::use(GLenum channel)
{
//    std::cout<<"Texture use called\n";
    if(Window::getActiveRenderer()==nullptr)
    {
        glActiveTexture(channel);
        glBindTexture(GL_TEXTURE_2D, this->GLTex);

    }
    return this->SDLTex;
}

Vec2f Texture::getGLCDimensions()
{
    return this->dimensions;
}

Vec2i Texture::getPxDimensions()
{
    // std::cout<<"("<<this->dimensions.x<<"|"<<this->dimensions.y<<")"<<"\n";
<<<<<<< HEAD

=======
//    std::cout<<"w:"<<this->dimensions.x<<"h:"<<this->dimensions.y<<"\n";
>>>>>>> Improved entity system. Some basic cleanup. Physics test
    return {Window::gLC2Px({this->dimensions.x,0}).x,Window::gLC2Px({0,this->dimensions.y}).y};
}


Vec2i Texture::getPxDimensions(Vec3f scale)
{
    // std::cout<<"("<<this->dimensions.x<<"|"<<this->dimensions.y<<")"<<"\n";
<<<<<<< HEAD

    return {Window::gLC2Px({this->dimensions.x*scale.x,0}).x,Window::gLC2Px({0,this->dimensions.y*scale.y}).y};
=======
     return {Window::gLC2Px({this->dimensions.x*scale.x,0}).x,Window::gLC2Px({0,this->dimensions.y*scale.y}).y};
>>>>>>> Improved entity system. Some basic cleanup. Physics test
}


Texture::~Texture()
{
    if(this->SDLTex)
    {
        SDL_DestroyTexture(this->SDLTex);
    }
    glDeleteTextures(1,&this->GLTex);
    std::cout<<"DESTROYED!!!!!!!!!!!!"<<"\n";
}
/*
template<>
string textureCT::name = "Texture";
*/
