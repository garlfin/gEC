//
// Created by scion on 9/13/2022.
//

#pragma once

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "Component.h"

struct Transformation;

class Transform : public Component {
public:
    Transform(Entity*, const Transformation *const = nullptr);

    union {
        glm::vec3 Location;
        glm::vec3 Position;
    };

    glm::vec3 Rotation;
    glm::vec3 Scale;

    glm::mat4 Model;

    void OnLoad() override;

    void OnUpdate(double d) override;

    void OnRender(double d) override;

    void OnFree() override;
};

struct Transformation {
    glm::vec3 Location;
    glm::vec3 Rotation;
    glm::vec3 Scale;
};
