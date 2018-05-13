#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include "componentBase.h"
#include <boost/uuid/uuid_generators.hpp>
#include <memory>
#include <iostream>
#define ENTITY_ERASE_UNPROTECTED 0
#define ENTITY_ERASE_PROTECTED 1

#define EN
class Entity
{
private:
    boost::uuids::uuid uuid;
    char protection = ENTITY_ERASE_UNPROTECTED;
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
        for(int i = 0; i < c; i ++)
        {
            mgrs[i]->copyTo(source,*this);
        }
    }

    void setProtection(bool status)
    {
        this->protection = status;
    }

    bool isProtected()const
    {
        return this->protection;
    }

    ~Entity()
    {
        std::cout<<"ENTITY WAS DELETED!!!!!!!!!!!"<<"\n";
        ComponentBase::removeGlobal(*this);
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
