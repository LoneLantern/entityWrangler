#ifndef TESTSYSTEM_H_INCLUDED
#define TESTSYSTEM_H_INCLUDED
#include "component.h"
#include "texture.h"
#include <unistd.h>
#include "transform.h"
#include "system.h"

using namespace component;

class TestSystem : public System{
private:
    textureCT &TexMgr;
    transformCT &TransMgr;
    float x;
public:
    TestSystem(textureCT &TexMgr, transformCT &TransMgr)
    :TexMgr(TexMgr),TransMgr(TransMgr)
    {
        std::cout<<"Constructing system"<<"\n";
        std::cout<<"Got manager(s) for types: "<<"\n";
        std::cout<<"\t*"<<this->TexMgr.getType().name()<<" | Hash:"<<this->TexMgr.getType().hash_code()<<"\n";
        std::cout<<"\t*"<<this->TransMgr.getType().name()<<" | Hash:"<<this->TransMgr.getType().hash_code()<<"\n";
        x=0.0f;
    }


    virtual void update(){
        int i = 0;
        for(auto it = this->TexMgr.begin(),end = this->TexMgr.end();it!=end;it++){
            auto *h = it->second.getHead();
            while(h){
                Node<std::shared_ptr<Transform>> *help = &this->TransMgr.get(it->first);
                while(help){
                    const Transform &trans = *help->getData();
                    float xVal = 16*pow((sin(x)),3)*-1;
                    float yVal = (13*cos(x)-5*cos(2*x)-2*cos(3*x)-cos(4*x))*-1;
                    Vec2i pos = Window::gLC2Px({trans.getPosition().x,trans.getPosition().y});
                    Vec2i scale = h->getData()->getPxDimensions(trans.getScale());
                    SDL_Rect rect = {pos.x,pos.y,scale.x,scale.y};
                    SDL_RenderCopy(Window::getActiveRenderer(),h->getData()->use(),NULL,&rect);
                    h=h->getNext();
                    x+=0.01f;
                    help=help->getNext();
                }
            }
        }
         //           getchar();

    }
};

#endif // TESTSYSTEM_H_INCLUDED
