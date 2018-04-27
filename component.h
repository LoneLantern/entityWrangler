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
#define ITERATE_COMP(mgr, itname) for(auto itname = mgr.begin(),_itend = mgr.end();itname!=_itend;itname++)

namespace COMPONENT_NAMESPACE_NAME
{
template <class t>
class Component : public ComponentBase
{
private:
    //std::vector<std::reference_wrapper<const Entity>> corpses;

    typedef typename std::unordered_map<std::reference_wrapper<const Entity>,List<std::shared_ptr<t>>,EntityHasher,std::equal_to<const Entity>> mapType;
    mapType componentMap;
    //static std::string name;
    template<typename... Args>
    void addList(const Entity &en, const std::shared_ptr<t> &ptr)
    {
//        std::cout<<".";
        this->componentMap.emplace(en,ptr);
//        std::cout<<".";
    }
    virtual void removeEnt(const Entity &en)
    {
        cout<<"Removing Corpse from map\n";
        this->componentMap.erase(en);
    }



protected:
public:
    typedef typename mapType::iterator iterator;

    virtual void copyTo(const Entity &source,const Entity &target)
    {
        cout<<"-";
        Node<shared_ptr<t>> *h = &this->get(source,0);
        while(h)
        {
            cout<<"-";
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
        /*  std::cout<<"Variadic was called with (";
          Component::doPrint(std::cout,args...);
          std::cout<<")\n";*/
        this->addTo(en,std::make_shared<t>(std::forward<Args>(args)...));
    }

    template < typename U, typename std::enable_if< std::is_base_of<t, U>::value, U>::type* = nullptr >
    void addTo( const Entity &en,U* ptr)
    {
        //   std::cout<<"Pointer was called\n";
        this->addTo(en,shared_ptr<t>(ptr));
    }
    void addTo(const Entity &en,const std::shared_ptr<t> ptr)
    {
        //   std::cout<<"Shared was called\n";
        try
        {
            List<std::shared_ptr<t>> *list = &this->getList(en);
            list->addNew(ptr);
        }
        catch(std::out_of_range)
        {
//            cout<<"adding list";
            this->addList(en,ptr);
        }
        this->registerToEntity(en);
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
        /*if(en.getStatus()==ENTITY_DEAD)
        {
            cout<<"Putting corpse on the pile";
            this->corpses.push_back(en);
            cout<<"-->done\n";
        }*/
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
//            std::cout<<"Entity "<<begin->first()<<" contains:\n";
            begin->second.printListContents();
        }
    }
    virtual void clearCorpses()
    {
        for(auto ent:this->corpses){
            this->componentMap.erase(ent);
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
