#include "lua.h"
#include "component.h"
#include <string>

sol::state Lua::lua;
sol::environment Lua::env(Lua::lua,sol::create);
bool Lua::wasInit = false;
