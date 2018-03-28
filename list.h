#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "node.h"

template<class t>
class List:InstanceCounted<List<t>>
{
private:
    typedef Node<t> NodeT;
    std::shared_ptr<NodeT> head;
    NodeT* tail;
    void initHead(const t &data)
    {
        this->head=std::make_shared<NodeT>(data);
        this->tail = &*this->head;
        this->head->setNext(nullptr);
        this->head->setPrev(nullptr);
    }
public:
    List()
    {}
    List(const t &data)
    {
        this->initHead(data);
    }
    List(List &&oth) = default;
    List(const List &oth) = default;

    NodeT* getHead()
    {
        return &*this->head;
    }


    void addNew(const t &data)
    {
        NodeT *last;
        try
        {
            last = &*this->tail;
            /*while(last&&last->getNext())
            {
                last=last->getNext();
            }*/
            last->setNext(new NodeT(data));
            last->getNext()->setPrev(last);
            this->tail = last->getNext();
        }
        catch(...)
        {
            if(!this->head)
            {
                this->initHead(data);
            }
        }
    }
    void removeFrom(const int id)
    {
        NodeT *last = &*this->head;
        register int i = 0;
        while(last&&last->getNext()&&i < id)
        {
            last=last->getNext();
            i++;
        }
        if(last==&*this->tail){
            this->tail = last->getPrev();
        }
        if(last==&*this->head)
        {
            this->head.reset(this->head->getNext());
        }
        else delete last;
    }

    void printListContents(){
        Node<t> *h = &*this->head;
        std::cout<<"---List<"<<typeid(t).name()<<"> start---"<<"\n";
        while(h){
            h->printNode();
            h=h->getNext();
        }
        std::cout<<"---List end---"<<"\n";
    }

    ~List(){
        Node<t> *h = &*this->head;
        while(h){
            Node<t> *helper = h;
            h=h->getNext();
            if(helper!=&*this->head)
                delete helper;
        }
    }
};

#endif // LIST_H_INCLUDED
