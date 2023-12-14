#ifndef UNIT_ENTITY_H
#define UNIT_ENTITY_H

#include <godot_cpp/core/class_db.hpp>
//#include <deps/flecs-math/vector.h>
#include <flecs/flecs.h>

namespace FlecsModule
{
    struct Position
    {
        //EcsVec3 vec3;
        float x, y, z;
    };

    struct Velocity
    {
        //EcsVec3 vec3;
        float x, y, z;
    };

    struct Target {
        //EcsVec3 vec3;
        float x, y, z;
    };

    struct Color
    {
        float r, g, b;
    };

    struct MultiMeshInstance
    {
        godot::RID id;
    };

    struct SpatialGrid {
        int x, y;
    };
}
#endif