#ifndef SYSTEMBASE_H_INCLUDED
#define SYSTEMBASE_H_INCLUDED
#include "instanceCounted.h"
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class System : InstanceCounted<System>{
private:
    typedef typename std::reference_wrapper<System> SystemRef;
    static std::vector<SystemRef> systemRegister;
    int id;
    void registerSelf(){
        System::systemRegister.push_back(*this);
        id=System::systemRegister.size()-1;
        cout<<"Reg"<<"\n";
    }
    void unregisterSelf(){
        System::systemRegister.erase(System::systemRegister.begin()+this->id);
    }
public:

    System(){
        this->registerSelf();
    }
    static const std::vector<SystemRef> getRegister(){
        return System::systemRegister;
    }
    virtual void update() = 0;

    ~System(){
        this->unregisterSelf();
    }
};

#endif // SYSTEMBASE_H_INCLUDED
