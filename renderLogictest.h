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

                    SDL_Rect rect = {pos.x,pos.y,scale.x,scale.y};
                    // std::cout<<trans.getRotation().z<<"\n";
                    SDL_SetRenderDrawColor(Window::getActiveRenderer(),255,0,0,255);
                    SDL_RenderCopyEx(Window::getActiveRenderer(),h->getData()->use(),NULL,&rect,trans.getRotation().z,NULL,SDL_FLIP_NONE);

                    SDL_RenderDrawRect(Window::getActiveRenderer(),&rect);

                    h=h->getNext();
                    x+=0.01f;
                    help=help->getNext();
                    if(rect.x<0){
                        std::cout<<"Entity outside screen: ("<<trans.getPosition2D().x<<"|"<<trans.getPosition2D().y<<")\n";
                    }
                }
            }
        }
    };
};

#endif // TESTSYSTEM_H_INCLUDED
