#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <memory>
#include <typeinfo>
#include "../utility/application.h"
#include "../utility/instanceCounted.h"
#include <iostream>

template<class t>
class Node:InstanceCounted<Node<t>>
{
private:
    std::shared_ptr<t> data;
    Node* next;
    Node* prev;
public:
    Node(const t& data)
        :data(std::make_shared<t>(data))
    {
        //std::cout<<"Constructing Node<"<<typeid(t).name()<<"> #"<<this->getInstanceCount()<<"\n";
        this->prev = this->next = nullptr;
    }
    t& getData()
    {
//        std::cout<<"Get data called...\n";
        return *this->data;
    }
    Node* getNext()
    {
        return this->next;
    }
    void setNext(Node* next)
    {
        this->next = next;
    }

    Node* getPrev()
    {
        return this->prev;
    }

    void setPrev(Node* prev)
    {
        this->prev = prev;
    }

    void printNode()
    {
        std::cout<<"* "<<*this->data<<"\n";
    }

    ~Node()
    {
        if(this->prev)
            this->prev->next = this->next;
        if(this->next)
            this->next->prev = this->prev;
    }
};

#endif // NODE_H_INCLUDED
