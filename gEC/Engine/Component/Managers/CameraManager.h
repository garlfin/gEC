//
// Created by scion on 9/14/2022.
//

#pragma once

#include "../Components/Camera.h"
#include "../../Asset/GLBuffer.h"

class CameraManager : public ComponentManager<Camera> {
private:
    const GLBuffer<CameraData> camBuffer;
public:
    explicit CameraManager(Window* window) : ComponentManager<Camera>(window), camBuffer(window) {};

    Camera* CurrentCamera;
    [[nodiscard]] Entity* const CurrentCameraOwner() const { return CurrentCamera->Owner(); }

    const GLBuffer<CameraData>* CamBuffer() { return &camBuffer; }

    void InitFrame();
};


