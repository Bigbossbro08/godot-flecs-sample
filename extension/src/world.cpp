#include "world.h"
#include <godot_cpp/core/class_db.hpp>
#include <flecs/flecs.h>
//#include <flecs/flecs_components_input.h>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <flecs_module.h>

//class flecs::components::input;

namespace FlecsModule
{
    World::World()
    {
        world = flecs::world();
        world.import<godot_flecs>();
        world.set<flecs::Rest>({});
        world.import <flecs::monitor>();
        world.set<RNG>({});
        //world.import<flecs::components::input>();
        flecs::log::set_level(2);
    }

    World::~World()
    {
    }

    flecs::world *World::get_world()
    {
        return &world;
    }

    void World::progress()
    {
        world.progress();
    }

    godot::String World::to_json()
    {
        return godot::String(world.to_json());
    }

    void World::_bind_methods()
    {
        godot::ClassDB::bind_method(godot::D_METHOD("progress"), &World::progress);
        godot::ClassDB::bind_method(godot::D_METHOD("to_json"), &World::to_json);
    }
}