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

    const float aspect = Owner()->Window()->Aspect();
    CamDat.Projection = glm::perspective(fov * DEG_TO_RAD, aspect, near, far);

    Transform* transform = Owner()->GetComponent<Transform>();

    CamDat.View = Window()->State() != WindowState::Skybox
                ?
                glm::translate(glm::mat4(1), -transform->Location)
                :
                glm::mat4(1);

    CamDat.View = glm::rotate(CamDat.View, -transform->Rotation.z * DEG_TO_RAD, glm::vec3(0, 0, 1));
    CamDat.View = glm::rotate(CamDat.View, -transform->Rotation.y * DEG_TO_RAD, glm::vec3(0, 1, 0));
    CamDat.View = glm::rotate(CamDat.View, -transform->Rotation.x * DEG_TO_RAD, glm::vec3(1, 0, 0));

    CamDat.View = glm::inverse(CamDat.View);
    CamDat.CameraPos = transform->Location;
    CamDat.OtherData = glm::vec4(fov, near, far, aspect);
}

void Camera::OnFree() {
}

Camera::Camera(Entity *owner, float n, float f, float fovY) : Component(owner, typeid(Camera)), near(n), far(f), fov(fovY) {

}

CameraData *Camera::Data() {
    return &CamDat;
}

void Camera::Set() {
    Window()->CamManager->CurrentCamera = this;
}
