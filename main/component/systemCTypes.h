#ifndef DEFAULTCOMPONENTTYPES_H_INCLUDED
#define DEFAULTCOMPONENTTYPES_H_INCLUDED
#include "component.h"
#include <string>


using namespace std;
namespace component
{
typedef Component<std::string> stringComponents;
typedef Component<int16_t> int16_tComponents;
typedef Component<int32_t> int32_tComponents;
typedef Component<int64_t> int64_tComponents;
typedef Component<uint16_t> uint16_tComponents;
typedef Component<uint32_t> uint32_tComponents;
typedef Component<uint64_t> uint64_tComponents;
typedef Component<char> charComponents;
typedef Component<bool> boolComponents;
typedef Component<float> floatComponents;
typedef Component<double> doubleComponents;
}
#endif // DEFAULTCOMPONENTTYPES_H_INCLUDED
