#include "component.h"
#include <UnitTest++.h>
using namespace component;

namespace
{
TEST(ComponentAddToTest)
{
    Component<int> intComp;
    Component<std::string> stringComp;

    Entity ent;
    intComp.addTo(ent,12);

    Component<std::string>::addByType(ent,"SomeString");
}
}

