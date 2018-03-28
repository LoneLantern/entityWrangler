#ifndef LUA_H_INCLUDED
#define LUA_H_INCLUDED
#include <sol.hpp>
#include <iostream>
#include "globalDefines.h"
#include "entity.h"
#define REGISTERCOMP_SELF(type) Lua::getState().new_usertype<type>(this->getName()+"CTType","addTo",&this->addTo,"get",&this->get,"remove",&this->remove);Lua::getState()[(this->getName()+"CT").c_str()];std::cout<<this->getName()+"CT"<<"\n";
#define REGISTERCOMP_TYPE(type,name,...) Lua::getEnv().new_usertype<type>(name,sol::constructors<__VA_ARGS__>())
#define REGISTER_ENTITY_CREATOR Lua::getEnv().new_usertype<UUID_RENAME>("Entity")


using namespace sol;
class Lua{
private:
    static state lua;
    load_result script;
    bool wasRunFrame;
    static bool wasInit;
    static sol::environment env;
    void init(){
        if(!wasInit){
            this->lua.open_libraries(sol::lib::base, sol::lib::package);
            REGISTER_ENTITY_CREATOR;
            Lua::wasInit = true;
        }
    }

public:
    Lua(){
        this->init();
    }
    void load(const char* file){
        try{
        script = this->lua.safe_script_file(file,Lua::env);
        std::cout<<"lol"<<"\n";
        }catch(const std::exception &err){
            std::cout<<err.what()<<"\n";
        }
    }

    load(std::string source){
        script = this->lua.load(source.c_str());
    }

    void run(){
        try{
        if(!this->wasRunFrame){
                        std::cout<<"run"<<"\n";

            this->script(Lua::env);
            this->wasRunFrame = true;
                    std::cout<<"ran successfully"<<"\n";

        }
        }catch(const std::exception &err){
            std::cout<<err.what()<<"\n";
        }

    }
    sol::function getFunc(const char* funcName){
        this->run();
        return this->lua[funcName];
    }
    static state& getState(){
        return Lua::lua;
    }
    static sol::environment getEnv(){
        return Lua::env;
    }


    ~Lua(){

    }
};


#endif // LUA_H_INCLUDED
