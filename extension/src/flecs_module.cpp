#include <flecs_module.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <world.h>
#include <deps/unit_entity.h>
#include <godot_cpp/classes/random_number_generator.hpp>
//#include <deps/flecs-math/vector.h>
//#define FLECS_MATH_EXPORT

class Node;
using namespace godot;

namespace FlecsModule
{
    godot_flecs::godot_flecs(flecs::world &ecs)
    {
        ecs.module<godot_flecs>();
        ecs.component<Position>().member<float>("x").member<float>("y").member<float>("z");
        ecs.component<Velocity>().member<float>("x").member<float>("y").member<float>("z");
        ecs.component<Color>().member<float>("r").member<float>("g").member<float>("b");
        ecs.component<SpatialGrid>().member<int>("x").member<int>("y");
        
        ecs.system<SpatialGrid, const Position>("SpatialGridSystem")
            .each([](SpatialGrid &s, const Position &p) {
                s.x = (int)(p.x / 10);
                s.y = (int)(p.z / 10);
            });

        //ecs.system<Velocity, const Position>("ChangeVelocity")
        //    .each([](Velocity &v, const Position &p)
        //          {    
        //            if (p.x > 100 || p.x < -100) {
        //                v.x *= -1;
        //            }
        //            if (p.y > 100 || p.y < -100) {
        //                v.y *= -1;
        //            }
        //            if (p.z > 100 || p.z < -100) {
        //                v.z *= -1;
        //            }
        //     });

        ecs.system<Position, const Velocity>("Move")
        .each([](Position &p, const Velocity &v) { 
            //ecs_vec3_add(p, v, p);
            p.x += v.x;
            p.y += v.y;
            p.z += v.z;
        });

        ecs.system<const Color, const MultiMeshInstance>("RenderColor")
            .each([](flecs::iter &it, size_t index, const Color &c, const MultiMeshInstance &i)
                  { RenderingServer::get_singleton()->multimesh_instance_set_color(i.id, index, godot::Color(c.r, c.g, c.b)); });

        //ecs.system<const RNG, Color, const SpatialGrid>("ColorIsPosition")
        //.term_at(1)
        //.singleton()
        //.each([](flecs::iter& it, size_t index, const RNG& rng_singleton, Color& c, const SpatialGrid& p) {
        //});

        // Create query that matches Gravity as singleton
        //flecs::query<RNG, Color, const SpatialGrid> q = 
        //ecs.query_builder<RNG, Color, const SpatialGrid>()
        //    .term_at(1).singleton()
        //    .build();

        ecs.system<RNG, Color, const SpatialGrid>("ColorIsPosition")
        .term_at(1).singleton()
        .each([](RNG& rng_singleton, Color& color, const SpatialGrid& sg) {
            //q.each([](RNG& rng_singleton, Color& color, const SpatialGrid& sg) {
                uint64_t i = (uint64_t) sg.x << 32 | sg.y;
                rng_singleton.rng->set_seed(i);
                color.r = rng_singleton.rng->randf_range(0, 1);
                color.g = rng_singleton.rng->randf_range(0, 1);
                color.b = rng_singleton.rng->randf_range(0, 1);
            //});
        });

        ecs.system<const Position, Velocity, const Target>("MoveTowards")
        .each([](flecs::iter &it, size_t index, const Position &p, Velocity &v, Target)
        {
           
        });
        //ecs.system(q);
        //q.each([](RNG& rng_singleton, Color& c, const SpatialGrid& p) {
        //});

        //ecs.system<RNG, Color, const SpatialGrid>("MySystem")
        //.term_at(1).singleton()
        //.each([](RNG& rng_singleton, Color& color, const SpatialGrid& sg) {
        //    rng_singleton.rng->set_seed(sg.x + sg.y);
        //    color.r = rng_singleton.rng->randf_range(0, 1);
        //    color.g = rng_singleton.rng->randf_range(0, 1);
        //    color.b = rng_singleton.rng->randf_range(0, 1);
        //});


        ecs.system<const Position, const MultiMeshInstance>("Render")
            .each([](flecs::iter &it, size_t index, const Position &p, const MultiMeshInstance &i)
                  { RenderingServer::get_singleton()->multimesh_instance_set_transform(i.id, index, Transform3D(Basis(), Vector3(p.x, p.y, p.z))); });
    }

}