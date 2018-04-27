#ifndef COLLIDABLE_H_INCLUDED
#define COLLIDABLE_H_INCLUDED
class AABB;
class Vec3f;
class Collidable{
public:
    bool collidesWith(const Vec3f &point)= 0;
    bool collidesWith(const AABB &other) = 0;
};

#endif // COLLIDABLE_H_INCLUDED
