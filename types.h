#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <boost/uuid/uuid.hpp>
#include <unordered_map>
#include <hashtable.h>
#include <boost/functional/hash.hpp>
#include "entity.h"
#define SYSTEM_NAMESPACE newSys


typedef Entity enid;

namespace SYSTEM_NAMESPACE
{
struct Rectangle
{
    float x;
    float y;
<<<<<<< HEAD
=======
    float z;
>>>>>>> Improved entity system. Some basic cleanup. Physics test
    float w;
    float h;
};

struct Tetragon
{
    float x1;
    float y1;
    float x2;
    float y2;
};

struct Vec2f
{
    float x;
    float y;
<<<<<<< HEAD
=======
        float Length(){
        return sqrt(x * x + y * y);
    }
    Vec2f Normalize(){
        Vec2f vector;
        float length = this->Length();

        if(length != 0){
            vector.x = y/length;
            vector.y = y/length;
        }

        return vector;
    }
>>>>>>> Improved entity system. Some basic cleanup. Physics test
};

struct Vec2i
{
    int32_t x;
    int32_t y;
<<<<<<< HEAD
=======
    // Normalizes the vector
    // Returns the length of the vector
    float Length(){
        return sqrt(x * x + y * y);
    }
    Vec2f Normalize(){
        Vec2f vector;
        float length = this->Length();

        if(length != 0){
            vector.x = y/length;
            vector.y = y/length;
        }

        return vector;
    }
>>>>>>> Improved entity system. Some basic cleanup. Physics test
};

struct Vec3f
{
    float x;
    float y;
    float z;
};

struct Vec3i
{
    int32_t x;
    int32_t y;
    int32_t z;
};
}

#endif // TYPES_H_INCLUDED
