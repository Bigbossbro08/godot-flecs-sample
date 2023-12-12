#ifndef GODOT_FLECS_MODULE_H
#define GODOT_FLECS_MODULE_H

#include <godot_cpp/core/class_db.hpp>
#include <flecs/flecs.h>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

namespace FlecsModule
{
    struct godot_flecs
    {
        godot_flecs(flecs::world &world); // Ctor that loads the module
    };
    
    struct RNG {
        std::shared_ptr<godot::RandomNumberGenerator> rng = std::make_shared<godot::RandomNumberGenerator>();
        //godot::RandomNumberGenerator rng = RandomNumberGenerator();
    };
}

#endif