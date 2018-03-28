#ifndef BULLETSYSTEM_H_INCLUDED
#define BULLETSYSTEM_H_INCLUDED
#include "system.h"
#include "entity.h"
#include "texture.h"
#include "component.h"
#include <iostream>
class BulletSystem:public System{
private:
    tagCT &TagMgr;
    transformCT &TransMgr;
    int run;
public:
    BulletSystem(tagCT &TagMgr,transformCT &transMgr)
    :TagMgr(TagMgr),TransMgr(transMgr),run(0){
    }
    virtual void update(){
        int i =0;

//        std::cout<<"bulletSystem";
        for(auto it = this->TagMgr.begin(),end = this->TagMgr.end();it!=end;it++){
            //std::cout<<it->first()<<"\n";
  //      std::cout<<"|";
           while(*(it->second.getHead()->getData())!="bullet"){
       //         std::cout<<"-->";
                it++;
            }
          //  std::cout<<"\n";
    //    std::cout<<"|";
            const Entity &h = it->first;
            const Transform &trans = *this->TransMgr.get(h).getData();

      //  std::cout<<"|";
            trans.setPosition({trans.getPosition().x+rand()%100/40000.0f,trans.getPosition().y+rand()%100/40000.0f - rand()%100/30000.0f,trans.getPosition().z});
//            cout<<trans.getPosition().x<<"|"<<trans.getPosition().y<<"|"<<trans.getPosition().z<<"\n";
        //std::cout<<"|";
        }
        //cout<<i<<"\n";
        this->run++;
    }

};

#endif // BULLETSYSTEM_H_INCLUDED
