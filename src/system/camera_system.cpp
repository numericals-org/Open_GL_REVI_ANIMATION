#include "camera_system.h"

CameraSystem::CameraSystem(unsigned int shader, GLFWwindow* window) {
    this->window = window;

    glUseProgram(shader);
    viewLocation = glGetUniformLocation(shader, "view");

    //Start with the cursor hidden at the centre so the first frame
    //doesn't read a big jump
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, 320.0, 240.0);
}

bool CameraSystem::update(
    std::unordered_map<unsigned int,TransformComponent> &transformComponents,
    unsigned int cameraID, CameraComponent& cameraComponent, float dt) {

    glm::vec3& pos = transformComponents[cameraID].position;
    glm::vec3& eulers = transformComponents[cameraID].euler;
    float theta = glm::radians(eulers.z);
    float phi = glm::radians(eulers.y);

    glm::vec3& right = cameraComponent.right;
    glm::vec3& up = cameraComponent.up;
    glm::vec3& forwards = cameraComponent.forwards;

    forwards = {
        glm::cos(theta) * glm::cos(phi),
        glm::sin(theta) * glm::cos(phi),
        glm::sin(phi)
    };
    right = glm::normalize(glm::cross(forwards, global_up));
    up = glm::normalize(glm::cross(right, forwards));

    glm::mat4 view = glm::lookAt(pos, pos + forwards, up);

    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

    //Keys
    glm::vec3 dPos = {0.0f, 0.0f, 0.0f};
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        dPos.x += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        dPos.y -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        dPos.x -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        dPos.y += 1.0f;
    }
    if (glm::length(dPos) > 0.1f) {
        dPos = glm::normalize(dPos);
        pos += 0.1f * dPos.x * forwards;
        pos += 0.1f * dPos.y * right;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        return true;
    }

    //Mouse: the cursor is put back at the window centre every frame,
    //so its offset from the centre is how far it moved this frame.
    //Skipped while the window is unfocused, since the cursor can't be
    //recentred then and the camera would keep spinning.
    glm::vec3 dEulers = {0.0f, 0.0f, 0.0f};
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        glfwSetCursorPos(window, 320.0, 240.0);

        dEulers.z = -0.1f * static_cast<float>(mouse_x - 320.0);
        dEulers.y = -0.1f * static_cast<float>(mouse_y - 240.0);
    }
    glfwPollEvents();

    eulers.y = fminf(89.0f, fmaxf(-89.0f, eulers.y + dEulers.y));

    eulers.z += dEulers.z;
    if (eulers.z > 360) {
        eulers.z -= 360;
    }
    else if (eulers.z < 0) {
        eulers.z += 360;
    }

    return false;
}