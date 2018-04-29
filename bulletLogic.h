#ifndef BULLETSYSTEM_H_INCLUDED
#define BULLETSYSTEM_H_INCLUDED
#include "programlogic.h"
#include "entity.h"
#include "texture.h"
#include "component.h"
#include <iostream>
# define M_PI           3.14159265358979323846  /* pi */
#include <cmath>
#include "iteratorTools.h"
#include "userInput.h"
#include "transform.h"

class BulletLogic:public ProgramLogic
{
private:
    component::tagComponents &TagMgr;
    component::transformComponents &TransMgr;
    Transform *playerPos = nullptr;

    int run;
public:
    BulletLogic(component::tagComponents &TagMgr,component::transformComponents &transMgr)
        :TagMgr(TagMgr),TransMgr(transMgr),run(0)
    {
        ITERATE_COMP(this->TagMgr,it)
        {
            /*while(it!=end&&(*(it->second.getHead()->getData()))!="player")
            {

                it++;
            }*/
            ITERATOR_FILTER_SKIP(it,_itend,(*it->second.getHead()->getData())!="player");
            if(it!=_itend)
                playerPos = &*TransMgr.get(it->first).getData();
        }
    }
    virtual void update()
    {

        ITERATE_COMP(this->TagMgr,it)
        {
            ITERATOR_FILTER_SKIP(it,_itend,(*it->second.getHead()->getData())=="player");
            if(it==_itend)
                break;

            const Entity &h = it->first;
            Transform &trans = *this->TransMgr.get(h).getData();
            Vec2f offset = {0.0f,0.01f};
            Vec2f dir = {0.0f,0.0f};
            if(playerPos!=nullptr)
            {
                offset = {playerPos->getPosition().x-trans.getPosition().x,trans.getPosition().y-playerPos->getPosition().y};
                dir = offset;
                offset.x *= missionControl::deltaTime()*2;
                offset.y *= missionControl::deltaTime()*2;

            }
            offset.x*=rand()%100/100.0f;
            offset.y*=rand()%100/100.0f;
            offset.x+=(rand()%100-50)/10000.0f;
            offset.y+=(rand()%100-50)/10000.0f;

            //  std::cout<<"|";
            trans.setPosition({trans.getPosition().x+offset.x,trans.getPosition().y-offset.y,trans.getPosition().z});
            Vec2f forward = {0.0f,1.0f};
            float dotProduct = {(dir.x*forward.x)+(dir.y*forward.y)};
            float rotation = dotProduct/(dir.Length()*forward.Length());
            rotation = acos(rotation);
            rotation = rotation*180.0f/M_PI;
            if(dir.x<0.0f)
            {
                rotation=360.0f-rotation;
            }
            if(dir.Length()<0.05f)
            {
                ComponentBase::removeGlobal(h);
            }
            trans.setRotation({0.0f,0.0f,rotation});
            Vec2i position = Window::gLC2Px(trans.getPosition2D());
            Vec2i playerPosition = Window::gLC2Px(playerPos->getPosition2D());
            SDL_SetRenderDrawColor(Window::getActiveRenderer(),255-(dir.Length()-0.3)*150,255-(dir.Length()-0.6)*150,255-(dir.Length()-0.9)*150,255);

            SDL_RenderDrawLine(Window::getActiveRenderer(),position.x,position.y,playerPosition.x,playerPosition.y);
            //cout<<trans.getPosition().x<<"|"<<trans.getPosition().y<<"|"<<trans.getPosition().z<<"\n";
            //std::cout<<"|";
        }
        //cout<<i<<"\n";
        this->run++;
    }

};

#endif // BULLETSYSTEM_H_INCLUDED
