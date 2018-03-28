#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED
#include <SDL/SDL_ttf.h>
#include <unordered_map>
#include "texture.h"
#include <memory>
#define FONTRENDER_START 33
#define FONTRENDER_END 126
class CharSet{
private:
    std::unordered_map<char,std::shared_ptr<Texture>> charMap;
    TTF_Font* assignedFont;
public:
    CharSet(TTF_Font *font);
    //Texture* get(const char character);
    std::shared_ptr<Texture> get(const char character);
    TTF_Font* getFont();

};

class Font{
private:
    std::unordered_map<uint8_t,std::unique_ptr<CharSet>> fontMap;
    TTF_Font *font = nullptr;
    uint8_t curSize;
public:
    Font(const char* path);

    Texture* get(const char character);
    void setSize(uint8_t size);

    ~Font();
};

#endif // FONT_H_INCLUDED
