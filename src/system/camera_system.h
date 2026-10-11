#pragma once
#include "../config.h"
#include "../components/camera_component.h"
#include "../components/transform_component.h"

class CameraSystem {
    public:
    CameraSystem(unsigned int shader, GLFWwindow* window);

    bool update(
        std::unordered_map<unsigned int, TransformComponent>& transfromComponent,
        unsigned int cameraID, CameraComponent& cameraComponent, float dt
    );

    private:
    unsigned int viewLocation;
    glm::vec3 global_up = {0.0f, 0.0f, 1.0f};
    GLFWwindow* window;
    bool looking = false;
    double last_mouse_x = 0.0, last_mouse_y = 0.0;
};