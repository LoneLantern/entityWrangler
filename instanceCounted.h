#ifndef INSTANCECOUNTED_H_INCLUDED
#define INSTANCECOUNTED_H_INCLUDED

#include <cstdint>

#define INSTANCE_COUNTED_COUNTERTYPE uint64_t


template <class t>
class InstanceCounted
{
private:
    static INSTANCE_COUNTED_COUNTERTYPE counter;
protected:
    static void increaseInstanceCount();
    static void decreaseInstanceCount();
public:
    InstanceCounted()
    {
        this->increaseInstanceCount();
    }

    ~InstanceCounted()
    {
        this->decreaseInstanceCount();
    }
    static INSTANCE_COUNTED_COUNTERTYPE getInstanceCount();

};

template <class t>
INSTANCE_COUNTED_COUNTERTYPE InstanceCounted<t>::counter = 0;

template <class t>
INSTANCE_COUNTED_COUNTERTYPE InstanceCounted<t>::getInstanceCount()
{
    return InstanceCounted<t>::counter;
}


template <class t>
void InstanceCounted<t>::increaseInstanceCount()
{
    InstanceCounted<t>::counter++;
}

template <class t>
void InstanceCounted<t>::decreaseInstanceCount()
{
    InstanceCounted<t>::counter--;
}
#endif // INSTANCECOUNTED_H_INCLUDED
