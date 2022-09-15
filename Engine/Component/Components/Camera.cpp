//
// Created by scion on 9/14/2022.
//

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../Entity.h"
#include "../../Windowing/Window.h"
#include "../../Misc/Math.h"
#include "Transform.h"

void Camera::OnLoad() {

}

void Camera::OnUpdate(double d) {

}

void Camera::OnRender(double d) {
    const float aspect = (float) Owner()->Window()->Size.x / Owner()->Window()->Size.y;
    CamDat.Projection = glm::perspective((float) (2 * atan(tan(0.5 * fov * DEG_TO_RAD)) * aspect), aspect, near, far);

    Transform* transform = Owner()->GetComponent<Transform>();

    const float pitch = std::clamp(transform->Rotation.x * DEG_TO_RAD, -89.0f, 89.0f);
    const float yaw = transform->Rotation.y * DEG_TO_RAD;

    Front.x = cos(glm::radians(yaw)) * cos(pitch);
    Front.y = sin(glm::radians(pitch));
    Front.z = sin(glm::radians(yaw)) * cos(pitch);
    Front = glm::normalize(Front);

    Right = glm::normalize(glm::cross(Front, glm::vec3(0, 1, 0)));
    Up = glm::normalize(glm::cross(Front, Up));

    CamDat.View = glm::lookAt(transform->Location, transform->Location + Front, Up);
    CamDat.CameraPos = transform->Location;
    CamDat.OtherData = glm::vec4(fov, near, far, aspect);
}

void Camera::OnFree() {
}

Camera::Camera(Entity *owner, float n, float f, float fovX) : Component(owner, typeid(Camera)), near(n), far(f), fov(fovX) {

}

CameraData *Camera::Data() {
    return &CamDat;
}

void Camera::Set() {
    Window()->CamManager->CurrentCamera = this;
}
