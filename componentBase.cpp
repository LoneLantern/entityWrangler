#include "componentBase.h"
<<<<<<< HEAD

std::vector<std::reference_wrapper<ComponentBase>> ComponentBase::componentList;


=======
#include "entity.h"
#include <algorithm>
std::vector<std::reference_wrapper<ComponentBase>> ComponentBase::componentList;


void ComponentBase::killEntity(const Entity &en){
    for(auto Ent:this->corpses){
        if(Ent.get()==en)
            return;
    }
    this->corpses.push_back(en);
}

void ComponentBase::registerToEntity(const Entity &target){
    if(std::find(target.attachedComponents.begin(),
                  target.attachedComponents.end(),
                  this)==target.attachedComponents.end())
        target.attachedComponents.push_back(this);
}


>>>>>>> Improved entity system. Some basic cleanup. Physics test

