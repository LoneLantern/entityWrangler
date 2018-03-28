#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include "componentBase.h"
#include <memory>
#include <iostream>

class Entity{
private:
    boost::uuids::uuid uuid;
public:
    const boost::uuids::uuid &operator ()()const{
        return this->uuid;
    }
    bool operator ==(const Entity &othr)const{
        return this->uuid==othr.uuid;
    }



    void copyComponents(const Entity &source,ComponentBase** mgrs, int c){
        for(int i = 0; i < c; i ++){
            mgrs[i]->copyTo(source,*this);
        }
    }
    ~Entity(){
        std::cout<<"ENTITY WAS DELETED!!!!!!!!!!!"<<"\n";
    }
};
struct EntityHasher{
    size_t operator()(const Entity& obj)const{
        return boost::uuids::hash_value((obj)());
    }

};


#endif // ENTITY_H_INCLUDED
