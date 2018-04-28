#ifndef COMPONENTBASE_H_INCLUDED
#define COMPONENTBASE_H_INCLUDED
#include "instanceCounted.h"
#include <typeinfo>
#include <vector>
#include <utility>
#include <functional>
#include <iostream>
#include <unordered_set>

class Entity;
class ComponentBase : InstanceCounted<ComponentBase>
{
private:
    bool enabled;
    const std::type_info& type;
    int id;
    static std::vector<std::reference_wrapper<ComponentBase>> componentList;
    void registerSelf()
    {
        ComponentBase::componentList.push_back(std::ref(*this));
        id=ComponentBase::componentList.size()-1;
    }
    void unregisterSelf()
    {
        ComponentBase::componentList.erase(ComponentBase::componentList.begin()+this->id);
    }

protected:
    void registerToEntity(const Entity &target);
    std::vector<std::reference_wrapper<const Entity>> corpses;

public:
    virtual void copyTo(const Entity &source,const Entity &target) = 0;

    ComponentBase(const std::type_info& type)
        :type(type)
    {
        this->enabled = true;
        this->registerSelf();
    }

    static const std::vector<std::reference_wrapper<ComponentBase>>& getComponentList()
    {
        return ComponentBase::componentList;
    }

    std::size_t operator()(const ComponentBase& k) const
    {
        return k.getType().hash_code();
    }

    bool isEnabled()
    {
        return this->enabled;
    }

    void setEnabled(bool enabled)
    {
        this->enabled = enabled;
    }

    const std::type_info &getType()const
    {
        return this->type;
    }

    template<class t>
    static ComponentBase &getComponent()
    {
        for(ComponentBase& component : ComponentBase::componentList)
        {
            if(typeid(t)==component.getType())
            {
                return component;
            }
        }
    }
    /*    template <class t>
        static ComponentBase getComponentTable(){
            std::cout<<"Function called on Entity"<<"\n";

            for(ComponentBase &comp:ComponentBase::getComponentList()){
                std::cout<<"looped"<<"\n";
                if(typeid(t).hash_code()==comp.getType().hash_code()){
                    std::cout<<"Component " << comp.getType().name()<<" seems to be a match for" << typeid(t).name()<<"\n";
                    return comp;
                }
            }
        }*/

    void killEntity(const Entity &en);

    virtual void clearCorpses() = 0;

    virtual ~ComponentBase()
    {
        this->unregisterSelf();
    }
};


#endif // COMPONENTBASE_H_INCLUDED
