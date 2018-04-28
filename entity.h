#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include "componentBase.h"
#include <boost/uuid/uuid_generators.hpp>
#include <memory>
#include <iostream>
#define ENTITY_ALIVE true
#define ENTITY_DEAD false
class Entity
{
private:
    boost::uuids::uuid uuid;
    bool protect = false;
    bool status = ENTITY_ALIVE;
    std::vector<ComponentBase*> attachedComponents;
    friend class ComponentBase;
public:
    Entity()
        :uuid(boost::uuids::random_generator()())
    {
    }
    const boost::uuids::uuid &operator ()()const
    {
        return this->uuid;
    }
    bool operator ==(const Entity &othr)const
    {
        return this->uuid==othr.uuid;
    }


    void copyComponents(const Entity &source,ComponentBase** mgrs, int c)
    {
        std::cout<<"copying...\n";
        for(int i = 0; i < c; i ++)
        {
            std::cout<<"-";
            mgrs[i]->copyTo(source,*this);
        }
    }
    void kill()
    {
        if(this->protect==false)
        {
            this->status = ENTITY_DEAD;
            for(ComponentBase* comp:this->attachedComponents)
            {
                comp->killEntity(*this);
            }
        }
    }
    bool getStatus()const
    {
        return this->status;
    }
    void setProtection(bool status)
    {
        this->protect = status;
    }

    bool getProtection()
    {
        return this->protect;
    }

    ~Entity()
    {
//        std::cout<<"ENTITY WAS DELETED!!!!!!!!!!!"<<"\n";
    }
};
struct EntityHasher
{
    size_t operator()(const Entity& obj)const
    {
        return boost::uuids::hash_value((obj)());
    }

};


#endif // ENTITY_H_INCLUDED
