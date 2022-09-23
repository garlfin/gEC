//
// Created by scion on 9/14/2022.
//

#pragma once

#include "Component.h"
#include "../../Struct/CameraData.h"

class Camera : public Component {
protected:
    float near, far, fov;
    CameraData CamDat;
public:
    Camera(Entity*, float n, float f, float fovY);

    void OnLoad() override;

    void OnUpdate(double d) override;

    virtual void OnRender(double d) override;

    void OnFree() override;

    CameraData* Data();

    glm::vec3 Front, Right, Up;

    void Set();
};
