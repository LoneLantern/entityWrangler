#ifndef TESTSYSTEM_H_INCLUDED
#define TESTSYSTEM_H_INCLUDED
#include "component.h"
#include "texture.h"
#include <unistd.h>
#include "transform.h"
#include "programlogic.h"
#include "iteratorTools.h"

using namespace component;

class RenderLogicTesst : public ProgramLogic
{
private:
    textureComponents &TexMgr;
    transformComponents &TransMgr;
    float x;
public:
    RenderLogicTesst(textureComponents &TexMgr, transformComponents &TransMgr)
        :TexMgr(TexMgr),TransMgr(TransMgr)
    {
        std::cout<<"Constructing system"<<"\n";
        std::cout<<"Got manager(s) for types: "<<"\n";
        std::cout<<"\t*"<<this->TexMgr.getType().name()<<" | Hash:"<<this->TexMgr.getType().hash_code()<<"\n";
        std::cout<<"\t*"<<this->TransMgr.getType().name()<<" | Hash:"<<this->TransMgr.getType().hash_code()<<"\n";
        x=0.0f;
    }


    virtual void update()
    {
        ITERATE_COMP(TexMgr,it)
        {

            auto *h = it->second.getHead();
            while(h)
            {
                Node<std::shared_ptr<Transform>> *help = &this->TransMgr.get(it->first);
                while(help)
                {
                    Transform &trans = *help->getData();
                    Vec2i pos = Window::gLC2Px({trans.getPosition().x,trans.getPosition().y});
                    Vec2i scale = h->getData()->getPxDimensions(trans.getScale());

                    Rectangle rect;
                    rect.h = scale.y;
                    rect.w = scale.x;
                    rect.x = pos.x;
                    rect.y = pos.y;
                     //std::cout<<"("<<rect.x<<"|"<<rect.y<<"|"<<rect.h<<"|"<<rect.w<<"\n";
                    SDL_SetRenderDrawColor(Window::getActiveWindow().getSDLRenderer(),255,0,0,255);
                    Window::getActiveRenderer()->drawTexture(*h->getData(),rect,trans.getRotation().z,{rect.w/2,rect.h/2});

                    //SDL_RenderCopyEx(Window::getActiveWindow().getSDLRenderer(),h->getData()->use(),NULL,&rect,trans.getRotation().z,NULL,SDL_FLIP_NONE);

                    //SDL_RenderDrawRect(Window::getActiveWindow().getSDLRenderer(),&rect);
                    Window::getActiveRenderer()->drawRectangle(rect);
                    h=h->getNext();
                    x+=0.01f;
                    help=help->getNext();
                }
            }
        }
    };
};

#endif // TESTSYSTEM_H_INCLUDED
