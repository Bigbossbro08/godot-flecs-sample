#include "camera_controller.h"

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/variant/rect2.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/classes/input.hpp>
//#include <godot_cpp/classes/camera3d.hpp>

using namespace godot;

namespace FlecsModule
{
    const int thickness = 5;
    CameraController::CameraController()
    {
    }

    CameraController::~CameraController()
    {
    }

    void CameraController::_ready() {
        //Input* input_handler = Input::get_singleton();
        //input_handler->set_mouse_mode(Input::MouseMode::MOUSE_MODE_CONFINED);
        camera = (Camera3D*)get_child(0);
        if (camera) {
            UtilityFunctions::print("Camera found!");
        }
        else {
            UtilityFunctions::print("Camera not found");
        }
    }

    void CameraController::_process(double delta) {
        if (Engine::get_singleton()->is_editor_hint()) { return; }

        Input* input_handler = Input::get_singleton();
        Vector3 moveDir = Vector3(0, 0, 0);
        if (input_handler != nullptr)
        {
            if (input_handler->is_key_pressed(KEY_W)) {
                moveDir.z += camera_speed;
            }
            if (input_handler->is_key_pressed(KEY_S)) {
                moveDir.z -= camera_speed;
            }
            if (input_handler->is_key_pressed(KEY_A)) {
                moveDir.x += camera_speed;
            }
            if (input_handler->is_key_pressed(KEY_D)) {
                moveDir.x -= camera_speed;
            }

            Viewport* viewport = get_viewport();
            Window* window = viewport->get_window();
            if (window->has_focus()) {
                Vector2 mousePosition = viewport->get_mouse_position();
                Rect2 visible_rect = viewport->get_visible_rect();
                Size2 size = visible_rect.size;
                if (mousePosition.x < thickness) {
                    moveDir.x += camera_speed;
                }
                if (mousePosition.y < thickness) {
                    moveDir.z += camera_speed;
                }
                if (mousePosition.x > size.width - thickness) {
                    moveDir.x -= camera_speed;
                }
                if (mousePosition.y > size.height - thickness) {
                    moveDir.z -= camera_speed;
                }
            }
            //UtilityFunctions::print(mousePosition);
        }

        translate_object_local(moveDir);
    }

    void CameraController::_bind_methods() {
	    ClassDB::bind_method(D_METHOD("get_camera_speed"), &CameraController::get_camera_speed);
	    ClassDB::bind_method(D_METHOD("set_camera_speed", "camera_speed"), &CameraController::set_camera_speed);
        ClassDB::add_property("CameraController", PropertyInfo(Variant::FLOAT, "camera_speed"), "set_camera_speed", "get_camera_speed");
    }
}