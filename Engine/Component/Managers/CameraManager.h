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
    CameraManager(Window* window) : camBuffer(window) {};

    Camera* CurrentCamera;
    Entity* const CurrentCameraOwner() { return CurrentCamera->Owner(); }

    const GLBuffer<CameraData>* const CamBuffer() { return &camBuffer; }

    void InitFrame()
    {
        camBuffer.ReplaceData(CurrentCamera->Data(), sizeof(CameraData));
    }
};

