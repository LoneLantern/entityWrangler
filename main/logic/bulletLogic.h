#ifndef BULLETSYSTEM_H_INCLUDED
#define BULLETSYSTEM_H_INCLUDED
#include "programlogic.h"
#include "../entity/entity.h"
#include "texture.h"
#include "../component/component.h"
#include <iostream>
# define M_PI           3.14159265358979323846  /* pi */
#include <cmath>
#include "../utility/iteratorTools.h"
#include "../utility/userInput.h"
#include "logger.h"
#include "../data/transform.h"

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
        bool drawn = false;
        bool alreadyIterated = false;

        ITERATE_COMP(this->TagMgr,it)
        {
            LOG<<"Iterated. Filtering out players\n";
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

            //  std::LOG<<"|";
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
            Vec2i playerCenter = {15,15};
            float collissionRadius = 0.2f;
            Vec2i playerPixelPos = Window::gLC2Px({playerPos->getPosition().x,playerPos->getPosition().y});
            Vec2f playerOffsetPos = Window::px2GLC({playerPixelPos.x+playerCenter.x,playerPixelPos.y+playerCenter.y});
            Vec2f distanceCenter = {trans.getPosition().x- playerOffsetPos.x,trans.getPosition().y-playerOffsetPos.y};
            Window::getActiveRenderer()->setStrokeWidth(10.0f);
            Window::getActiveRenderer()->setColor(1.0f-distanceCenter.Length()/2.0f,0.0f,distanceCenter.Length()/2.0f,1.0-distanceCenter.Length()/4.0f);
           //Window::getActiveRenderer()->drawCircle(Window::gLC2Px({playerOffsetPos.x,0.0f}).x,Window::gLC2Px({0.0f,playerOffsetPos.y}).y,Window::gLC2Px({distanceCenter.Length()-1,0.0f}).x,false);
            if(drawn == false){
                Window::getActiveRenderer()->setColor(0.0f,0.0f,0.5f,1.5f);
                Window::getActiveRenderer()->drawCircle(Window::gLC2Px({playerOffsetPos.x,0.0f}).x,Window::gLC2Px({0.0f,playerOffsetPos.y}).y,Window::gLC2Px({collissionRadius-1,0.0f}).x,false);
                drawn = true;
            }

            trans.setRotation({0.0f,0.0f,rotation});
            Vec2i position = Window::gLC2Px(trans.getPosition2D());
            Vec2i playerPosition = Window::gLC2Px(playerPos->getPosition2D());
            SDL_SetRenderDrawColor(Window::getActiveWindow().getSDLRenderer(),255-(dir.Length()-0.3)*150,255-(dir.Length()-0.6)*150,255-(dir.Length()-0.9)*150,255);
            if(distanceCenter.Length()<collissionRadius+0.05)
            {
                LOG<<"Removing from "<<h()<<"\n";
                LOG<<"Getting Entity Data Adresses\n";
                std::string *sPtr = &*this->TagMgr.get(h).getData();
                Transform *tPtr = &*this->TransMgr.get(h).getData();
                auto holderPartie = this->TagMgr.get(h).getData();
                ComponentBase::removeGlobal(h);
                LOG<<"Crah-Testing Entity Data integrety..."<<"\n";
                LOG<<"Address of sPtr: "<< sPtr<< "\n";
                LOG<<"Contents of sPtr: "<<sPtr->c_str()<<"\n";
                LOG<<"Address of tPtr: "<< tPtr<< "\n";
                LOG<<"Contents of tPtr: "<< tPtr->getPosition().x << "|" << tPtr->getPosition().y<< "\n";
                if(it==_itend)
                    break;
                else{
                    LOG<<"There should be one more element! Peeking...\n";
                auto copy = it;
                copy++;
                copy->first;
                copy->second;
                if(copy==_itend){
                    LOG<<"\tshould be last!\n";
                }else{
                    LOG<<"\tshould belong to "<<copy->first()<<"\n";
                }
                LOG<<"-> Removal complete. Proceeding...\n";
                }
            }
            //SDL_RenderDrawLine(Window::getActiveWindow().getSDLRenderer(),position.x,position.y,playerPosition.x,playerPosition.y);
            //LOG<<trans.getPosition().x<<"|"<<trans.getPosition().y<<"|"<<trans.getPosition().z<<"\n";
            //std::LOG<<"|";*/
        }
        LOG<<"Finished one round\n";
        //LOG<<i<<"\n";
        this->run++;
    }

};

#endif // BULLETSYSTEM_H_INCLUDED
