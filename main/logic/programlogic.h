#ifndef SYSTEMBASE_H_INCLUDED
#define SYSTEMBASE_H_INCLUDED
#include "../utility/instanceCounted.h"
#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class ProgramLogic : InstanceCounted<ProgramLogic>
{
private:
    typedef typename std::reference_wrapper<ProgramLogic> SystemRef;
    static std::vector<SystemRef> systemRegister;
    int id;
    void registerSelf()
    {
        ProgramLogic::systemRegister.push_back(*this);
        id=ProgramLogic::systemRegister.size()-1;
        cout<<"Reg"<<"\n";
    }
    void unregisterSelf()
    {
        ProgramLogic::systemRegister.erase(ProgramLogic::systemRegister.begin()+this->id);
    }
public:

    ProgramLogic()
    {
        this->registerSelf();
    }
    static const std::vector<SystemRef> getRegister()
    {
        return ProgramLogic::systemRegister;
    }
    virtual void update() = 0;

    ~ProgramLogic()
    {
        this->unregisterSelf();
    }
};

#endif // SYSTEMBASE_H_INCLUDED
