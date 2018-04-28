#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

struct Mail
{
    const std::string message;
    const MessageCenter& source;
};


class PostOffice
{
private:
    std::vector<std::reference_wrapper<Message>> msgStack;
    virtual void storeMessage(std::string message,const MessageCenter& sender)
    {

    }
public:
    static const MessageCenter GLOBAL;
    void send(const std::string &message,const MessageCenter& target);
    Message* pull();
    Message* peek();
    Message* get(const string &msg);
};



#endif // MESSAGE_H_INCLUDED
