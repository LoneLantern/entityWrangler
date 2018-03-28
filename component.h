#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED
#include <boost/uuid/uuid.hpp>
#include <unordered_map>
#include <utility>
#include <boost/functional/hash.hpp>
#include "instanceCounted.h"
#include "list.h"
#include "globalDefines.h"
#include "parser.h"
#include "componentBase.h"
#include "entity.h"
#include <memory>
#define UUID_RENAME Entity

namespace COMPONENT_NAMESPACE_NAME
{
template <class t>
class Component : public ComponentBase
{
private:
    typedef typename std::unordered_map<std::reference_wrapper<const Entity>,List<std::shared_ptr<t>>,EntityHasher,std::equal_to<const Entity>> mapType;
    mapType componentMap;
    //static std::string name;
    template<typename... Args>
    void addList(const Entity &en, const std::shared_ptr<t> &ptr)
    {
        this->componentMap.insert(std::pair<std::reference_wrapper<const Entity>,List<std::shared_ptr<t>>>(en,ptr));
    }
protected:
public:
    typedef typename mapType::iterator iterator;

    virtual void copyTo(const Entity &source,Entity &target)
    {
        Node<shared_ptr<t>> *h = &this->get(source);
        while(h)
        {
            this->addTo(target,*h->getData());
            h=h->getNext();
        }
    }
    Component()
        :ComponentBase(typeid(t))
    {
    }
    Component(const Component & othr)
    {
        this->componentMap = othr.componentMap;
    }

    List<std::shared_ptr<t>>& operator[](const Entity &en)
    {
        return this->componentMap[en];
    }
    List<std::shared_ptr<t>>& getList(const Entity &en)
    {
        return this->componentMap.at(en);
    }
    template<typename... Args>
    void addTo(const Entity &en, Args...args)
    {
        try
        {
            auto & l= this->getList(en);
            l.addNew(std::make_shared<t>(std::forward<Args>(args)...));
        }
        catch(std::out_of_range ex)
        {
            this->addList(en,std::make_shared<t>(std::forward<Args>(args)...));
        }
    }

    template < typename U, typename std::enable_if< std::is_base_of<t, U>::value, U>::type* = nullptr >
    void addTo( const Entity &en,U* ptr)
    {
        std::cout<<"New addTo called with ptr ("<<ptr<<")\n";
         try
        {
            std::cout<<"New add to tries to add new to existing list...\n";
            const List<std::shared_ptr<t>> &list = this->getList(en);
            std::cout<<"Recieved list...\n";
            list.addNew(shared_ptr<t>(ptr));
        }catch(std::out_of_range){
            std::cout<<"Failed! \n";
            std::cout<<"Trying to add new list\n";
            this->addList(en,shared_ptr<t>(ptr));
            std::cout<<"Added new List OK. \n";
            std::cout<<"\n";
        }
    }
    template<typename... Args>
    static int addByType(const Entity &en, Args...args)
    {
        Component<t> *compType = NULL;
        try
        {
            compType = dynamic_cast<Component<t>*>(&ComponentBase::getComponent<t>());
            if(compType==NULL)
            {
                throw std::bad_cast();
            }
            compType->addTo(en,std::forward<Args>(args)...);
        }
        catch(std::bad_cast ex)
        {
            std::cout<<"Something went wrong creating the type. Maybe an instance couldnt be found or the dynamic cast is broken"<<"\n";
        }
    }


    Node<std::shared_ptr<t>> &get(const Entity &en,const uint16_t id = 0)
    {
        auto* start = this->getList(en).getHead();
        register uint16_t i = 0;
        while(i<id)
        {
            start = start->getNext();
            i++;
        }
        return *start;
    }

    void remove(const Entity &en,const uint16_t id)
    {
        this->getList(en).removeFrom(id);
    }

    iterator begin()
    {
        return this->componentMap.begin();
    }


    iterator end()
    {
        return this->componentMap.end();
    }

    void printTableContents()
    {
        for(auto begin = this->componentMap.begin(), end = this->componentMap.end();
                begin!=end; begin++)
        {
            std::cout<<"Entity "<<begin->first()<<" contains:\n";
            begin->second.printListContents();
        }
    }

    virtual ~Component() = default;
};

}

namespace component
{
typedef Component<std::string> tagCT;

}
#endif // COMPONENT_H_INCLUDED
