#ifndef CAMERA_CONTROLLER_CLASS_H
#define CAMERA_CONTROLLER_CLASS_H

#include <godot_cpp/core/class_db.hpp>
#include <flecs/flecs.h>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <world.h>

using namespace godot;

namespace FlecsModule
{
    class CameraController : public Node3D {
        GDCLASS(CameraController, Node3D);
    protected:
        static void _bind_methods();

    public:
        // property
        float camera_speed;
        Camera3D* camera;
        // functions
        CameraController();
        ~CameraController();
        void _ready();
        void _process(double delta) override;
        float get_camera_speed() const { return camera_speed; }
        void set_camera_speed(float speed) { camera_speed = speed; }
    };
}
#endif