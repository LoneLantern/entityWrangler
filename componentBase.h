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
    static std::vector<std::reference_wrapper<ComponentBase>> instances;
    void registerSelf()
    {
        ComponentBase::instances.push_back(std::ref(*this));
        id=ComponentBase::instances.size()-1;
    }
    void unregisterSelf()
    {
        ComponentBase::instances.erase(ComponentBase::instances.begin()+this->id);
    }

protected:
    virtual void removeAllowed(const Entity &en) = 0;
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
        return ComponentBase::instances;
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
        for(ComponentBase& component : ComponentBase::instances)
        {
            if(typeid(t)==component.getType())
            {
                return component;
            }
        }
        throw std::out_of_range("Component could not be located");
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

    virtual void remove(const Entity &target);

    static void removeGlobal(const Entity &target){
        for(ComponentBase &base:ComponentBase::instances){
            base.remove(target);
        }
    }

    virtual ~ComponentBase()
    {
        this->unregisterSelf();
    }
};


#endif // COMPONENTBASE_H_INCLUDED
