#include "font.h"
#include <SDL/SDL.h>
#include <iostream>


static void initSystems(){
    /*if(!SDL_WasInit(SDL_INIT_VIDEO) && SDL_Init(SDL_INIT_VIDEO )==-1){
            throw std::runtime_error("SDL_Video_Init Err");
    }*/
    if(!TTF_WasInit() && TTF_Init()==-1) {
        throw std::runtime_error("TTF_Init Err");
    }
}
CharSet::CharSet(TTF_Font *font)
:assignedFont(font){
    initSystems();
    for(char c=FONTRENDER_START;c<=FONTRENDER_END;c++){
        SDL_Color black;
        black.r=black.g=black.b=255;
        black.a=255;
        SDL_Surface *character = TTF_RenderGlyph_Blended(font,c,black);
       /* std::string stat("./");
        stat+=std::to_string((int)c);
        stat+=".bmp";
        SDL_SaveBMP(character,stat.c_str());*/
        std::cout<<SDL_GetError()<<TTF_GetError()<<"\n";
        this->charMap.insert(std::pair<char,std::shared_ptr<Texture>>(c,std::make_shared<Texture>(character)));
    }
}/*
Texture* CharSet::get(const char character){
    return &*this->charMap.at(character);
}*/

std::shared_ptr<Texture> CharSet::get(const char character){
    return this->charMap.at(character);
}
TTF_Font* CharSet::getFont(){
    return this->assignedFont;
}

