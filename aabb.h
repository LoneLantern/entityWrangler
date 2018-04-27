#pragma once
#include "types.h"
#include "collidable.h"
#include <limits>

class AABB:public Collidable{
private:
    SYSTEM_NAMESPACE::Vec3f min;
    SYSTEM_NAMESPACE::Vec3f max;

public:
    AABB(float x1, float x2, float y1, float y2, float z1 = -std::numeric_limits<float>::infinity(),float z2 = std::numeric_limits<float>::infinity()){
        this->min = {x1,y1,z1};
        this->depth = {x2,y2,z2};
    }
    bool collidesWith(const Vec3f &point){//A point
        return (point.x >= box.minX && point.x <= box.maxX) &&
         (point.y >= box.minY && point.y <= box.maxY) &&
         (point.z >= box.minZ && point.z <= box.maxZ);
    }
    bool collidesWith(const AABB &other){//Another AABB
        return (this->min.x <= other.max.x && this->max.x >= other.min.x) &&
         (this->min.y <= other.max.y && this->max.y >= other.min.y) &&
         (this->min.z <= other.max.z && this->max.z >= other.min.z);
    }
};
