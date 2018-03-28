#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <string>
#include <cstring>
using namespace std;
class Parser{
public:


    static void parse(const char* data,int16_t &out){
        out = std::stoi(data);
    }
    static void parse(const char* data,int32_t &out){
        out = std::stoi(data);
    }
    static void parse(const char* data,int64_t &out){
        out = std::stoi(data);
    }
    static void parse(const char* data,uint16_t &out){
        out = std::stoi(data);
    }
    static void parse(const char* data,uint32_t &out){
        out = std::stoi(data);
    }
    static void parse(const char* data,uint64_t &out){
        out = std::stoi(data);
    }
    static void parse(const char* data,char &out){
        out = data[0];
    }
    static void parse(const char* data,bool &out){
        out = (strcmp(data,"true")?true:false);
    }
    static void parse(const char* data,float &out){
        out = std::stof(data);
    }
    static void parse(const char* data,double &out){
        out = std::stof(data);
    }
    static void parse(const char* data,string &out){
        out = std::string(data);
    }

};

#endif // PARSER_H_INCLUDED
