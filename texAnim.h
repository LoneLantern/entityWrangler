#ifndef TEXANIM_H_INCLUDED
#define TEXANIM_H_INCLUDED
#include "texture.h"
#include <vector>
#include <memory>
#include <string>



class TexAnim:public Texture
{
private:
    std::vector<std::shared_ptr<Texture>> frames;
    std::string name;
    float fps;
    float time_start;

    void initFromFolder(const char* folder);

public:
    TexAnim(const char* folder,float fps);

    SDL_Texture* use(GLenum channel = GL_TEXTURE0);
    Texture* get();
    virtual Vec2i getPxDimensions();
    virtual Vec2i getPxDimensions(Vec3f scale);
};


#endif // TEXANIM_H_INCLUDED
