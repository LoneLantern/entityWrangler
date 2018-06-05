#ifndef BLUEPRINT_H_INCLUDED
#define BLUEPRINT_H_INCLUDED
#include "entity.h"
#include "../component/component.h"

class Blueprint
{
private:
    std::vector<std::function<void(Entity &)>> functions;
public:
    template < typename T, typename U, typename std::enable_if< std::is_base_of<T, U>::value, U>::type* = nullptr>
    void linkWith(Component<T>& comp, U* ptr)
    {
        cout<<"Alternate linkWith called !\n";
        this->linkWith(comp,shared_ptr<T>(ptr));
    }

    template<typename T, typename... Args>
    void linkWith(Component<T>& comp, Args...args)
    {
        cout<<"Default linkWith called !\n";
        functions.emplace_back([=, &comp](Entity& ent)
        {
            comp.addTo(ent, args...);
        });
    }



    void applyOnto(Entity &en)
    {
        for(const auto& f : functions){
            f(en);
        }
    }
};

#endif // BLUEPRINT_H_INCLUDED
