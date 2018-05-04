#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED
#include <SDL/SDL_ttf.h>
#include <unordered_map>
#include "texture.h"
#include "SDL_FontCache.h"
#include <memory>
#define FONTRENDER_START 32
#define FONTRENDER_END 126/*
class CharSet
{
private:
    std::unordered_map<char,std::shared_ptr<Texture>> charMap;
    TTF_Font* assignedFont;
public:
    CharSet(TTF_Font *font);
    //Texture* get(const char character);
    std::shared_ptr<Texture> get(const char character);
    TTF_Font* getFont();

};*/

class Font
{
private:
    FC_Font *font;
public:
    Font(const char* path, uint8_t size = 16, int r=255,int g=255,int b=255);

    void draw(const char* text,int x,int y);
    //void setSize(uint8_t size);
};

#endif // FONT_H_INCLUDED
