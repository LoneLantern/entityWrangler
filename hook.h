#ifndef HOOK_H_INCLUDED
#define HOOK_H_INCLUDED
#include <unordered_map>
#include <boost/any.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/function.hpp>
#include <map>
#include <string>
#include <iostream>
#include "list.h"
#include "action.h"/*
class typeErasedFunction
{
private:
    boost::any anyFunction;
public:
    template<class F>
    typeErasedFunction(F fun)
    :typeErasedFunction(boost::function(fun)){
    }
    template<class...Args>
    typeErasedFunction(boost::function<void(Args...)>func)
    :anyFunction(func)
    {
    }
    template<class...Args>
    void operator()(Args...args){
        boost::any_cast<std::function<void(Args...)>>(this->anyFunction)(std::forward<Args>(args)...);
    }
};


/*
template<>
class AnyFunction<void>{
private:
    std::any storedFunction;
public:
    AnyFunction(){
    };

    template <typename ... Args>
    AnyFunction(std::function<void(Args...) func)
    :storedFunction(func){
    }

    template <typename ... Args>
    ret operator()(Args&&... args){
        return std::invoke(std::any_cast<std::function<void(Args...)>(this->storedFunction),std::forward(args)...);
    }
};
*/

/*
class Hook{
private:
    static std::unordered_map<std::string,List<typeErasedFunction>> hookedFunctions;
public:
    template<class F>
    static void add(const char* hook,F&& func){
        Hook::hookedFunctions.emplace(hook,typeErasedFunction(func));
    }
    template<class...Args>
    static void call(const char* hook,Args&&...args){
        auto list = Hook::hookedFunctions[hook];
        auto h = list.getHead();
        while(h){
            h->getData()(args...);
            h=h->getNext();
        }
    }
};*/


#endif // HOOK_H_INCLUDED
