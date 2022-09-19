//
// Created by scion on 9/13/2022.
//

#include "Transform.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/matrix.hpp"
#include "../../Misc/Math.h"
#include "../Entity.h"

void Transform::OnLoad() {

}

void Transform::OnUpdate(double d)
{
    Model = glm::scale(glm::translate(glm::mat4(1), Location), Scale);
    Model = glm::rotate(Model, Rotation.z * DEG_TO_RAD, glm::vec3(0, 0, 1));
    Model = glm::rotate(Model, Rotation.y * DEG_TO_RAD, glm::vec3(0, 1, 0));
    Model = glm::rotate(Model, Rotation.x * DEG_TO_RAD, glm::vec3(1, 0, 0));

    const float pitch = std::clamp(Rotation.x, -89.0f, 89.0f) * DEG_TO_RAD;
    const float yaw = Rotation.y * DEG_TO_RAD;

    Front.x = glm::cos(yaw) * glm::cos(pitch);
    Front.y = glm::sin(pitch);
    Front.z = glm::sin(yaw) * glm::cos(pitch);
    Front = glm::normalize(Front);

    Right = glm::normalize(glm::cross(Front, glm::vec3(0, 1, 0)));
    Up = glm::normalize(glm::cross(Right, Front));

    if (Owner() && Owner()->GetComponent<Transform>()) { Model *= Owner()->GetComponent<Transform>()->Model; }
}

void Transform::OnRender(double d) {

}

void Transform::OnFree() {

}

Transform::Transform(class Entity* parent, const Transformation* const transformation) :
        Component(parent, typeid(Transform))
        , Location(transformation ? transformation->Location : glm::vec3(0))
        , Rotation(transformation ? transformation->Rotation : glm::vec3(0))
        , Scale(transformation ? transformation->Scale : glm::vec3(1))
        { }


