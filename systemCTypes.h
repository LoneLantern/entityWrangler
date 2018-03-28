#ifndef DEFAULTCOMPONENTTYPES_H_INCLUDED
#define DEFAULTCOMPONENTTYPES_H_INCLUDED
#define COMPONENT_NAMESPACE_NAME component
#include "component.h"
#include <string>
#include "globalDefines.h"


using namespace std;
namespace COMPONENT_NAMESPACE_NAME{
typedef Component<std::string> stringCT;
typedef Component<int16_t> int16_tCT;
typedef Component<int32_t> int32_tCT;
typedef Component<int64_t> int64_tCT;
typedef Component<uint16_t> uint16_tCT;
typedef Component<uint32_t> uint32_tCT;
typedef Component<uint64_t> uint64_tCT;
typedef Component<char> charCT;
typedef Component<bool> boolCT;
typedef Component<float> floatCT;
typedef Component<double> doubleCT;
}
#endif // DEFAULTCOMPONENTTYPES_H_INCLUDED
