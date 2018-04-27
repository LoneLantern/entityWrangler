#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED
#include <functional>
#include <tuple>

/*
template<class Ret, class...Args>
class Action{
private:
    std::function<Ret(Args...)> funcStored;
    std::tuple<Args...> funcArguments;
public:
    template<class F,class...FuncArgs>
    Action(F&& func,FuncArgs&&...args)
    :funcStored(func),
    funcArguments(args...){
    }
    Ret& act(){
        return this->funcStored(this->funcArguments);
    }
};*/

class Action{
private:
    std::function<void()> funcStored;
public:
    template<class F,class...FuncArgs>
    Action(F&& func,FuncArgs&&...args){
        this->funcStored = [func, args...]()
        {
            (func)(args...);
        };
    }
    void act(){
        this->funcStored();
    }
};/*
template<>
class Action<void>{
private:
    std::function<void(void)> funcStored;
public:
    template<class F>
    Action(F&& func){
        this->funcStored = func;
    }
    void act(){
        this->funcStored();
    }
};*/
#endif // ACTION_H_INCLUDED
