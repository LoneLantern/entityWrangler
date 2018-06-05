#include "componentBase.h"
#include "../entity/entity.h"
#include <algorithm>
std::vector<std::reference_wrapper<ComponentBase>> ComponentBase::instances;


void ComponentBase::remove(const Entity &target){
        if(target.isProtected()==ENTITY_ERASE_UNPROTECTED){
            this->removeAllowed(target);
            //this->unregisterSelf();
        }
};
