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
};

struct Vec2i
{
    int32_t x;
    int32_t y;
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
