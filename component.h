#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED
#include <boost/uuid/uuid.hpp>
#include <unordered_map>
#include <utility>
#include <boost/functional/hash.hpp>
#include "instanceCounted.h"
#include "list.h"
#include "parser.h"
#include "componentBase.h"
#include "entity.h"
#include <memory>
#define Entity Entity
#define ITERATE_COMP(mgr, itname) for(auto itname = mgr.begin(),_itend = mgr.end();itname!=_itend;itname++)

namespace component
{
template <class t>
class Component : public ComponentBase
{
private:
    //std::vector<std::reference_wrapper<const Entity>> corpses;

    typedef typename std::unordered_map<std::reference_wrapper<const Entity>,List<std::shared_ptr<t>>,EntityHasher,std::equal_to<const Entity>> entityComponentMapType;
    entityComponentMapType components;
    //static std::string name;
    template<typename... Args>
    void addList(const Entity &en, const std::shared_ptr<t> &ptr)
    {
//        std::cout<<".";
        this->components.emplace(en,ptr);
//        std::cout<<".";
    }

    virtual void removeAllowed(const Entity &en){
        this->components.erase(en);
    }


protected:
public:
    typedef typename entityComponentMapType::iterator iterator;

    virtual void copyTo(const Entity &source,const Entity &target)
    {
//        cout<<"-";
        Node<shared_ptr<t>> *h = &this->get(source,0);
        while(h)
        {
            //cout<<"-";
            this->addTo(target,h->getData());
            h=h->getNext();
        }
    }
    Component()
        :ComponentBase(typeid(t))
    {
    }
    Component(const Component & othr)
    {
        this->components = othr.components;
    }

    List<std::shared_ptr<t>>& operator[](const Entity &en)const
    {
        return this->components[en];
    }

    List<std::shared_ptr<t>>& getList(const Entity &en)
    {
        return this->components.at(en);
    }
    template <typename Arg, typename... Args>
    static void doPrint(std::ostream& out, Arg&& arg, Args&&... args)
    {
        out << std::forward<Arg>(arg);
        using expander = int[];
        (void)expander{0, (void(out << ',' << std::forward<Args>(args)),0)...};
    }
    template<typename... Args>
    void addTo(const Entity &en, Args...args)
    {
        this->addTo(en,std::make_shared<t>(std::forward<Args>(args)...));
    }

    template < typename U, typename std::enable_if< std::is_base_of<t, U>::value, U>::type* = nullptr >
    void addTo( const Entity &en,U* ptr)
    {
        this->addTo(en,shared_ptr<t>(ptr));
    }
    void addTo(const Entity &en,const std::shared_ptr<t> ptr)
    {
        try
        {
            List<std::shared_ptr<t>> *list = &this->getList(en);
            list->addNew(ptr);
        }
        catch(std::out_of_range)
        {
            this->addList(en,ptr);
        }
    }
    template<typename... Args>
    static void addByType(const Entity &en, Args...args)
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
        return this->components.begin();
    }


    iterator end()
    {
        return this->components.end();
    }

    void printTableContents()const
    {
        for(auto begin = this->components.begin(), end = this->components.end();
                begin!=end; begin++)
        {
            begin->second.printListContents();
        }
    }


    virtual ~Component() = default;
};

typedef Component<std::string> tagComponents;

}


#endif // COMPONENT_H_INCLUDED
