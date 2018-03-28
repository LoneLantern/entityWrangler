#include "component.h"
#include <UnitTest++.h>
using namespace COMPONENT_NAMESPACE_NAME;

namespace
{
    TEST(ComponentAddToTest){
        Component<int> intComp;
        Component<std::string> stringComp;

        Entity ent;
        intComp.addTo(ent,12);

        Component<std::string>::addByType(ent,"SomeString");
    }
}

