//
// Created by scion on 9/14/2022.
//

#ifndef IME_CAMERAMANAGER_H
#define IME_CAMERAMANAGER_H


#include "../Components/Camera.h"
#include "../../Asset/GLBuffer.h"

class CameraManager : public ComponentManager<Camera> {
private:
    GLBuffer<CameraData> camBuffer;
public:
    CameraManager(Window* window) : camBuffer(window) {};

    Camera* CurrentCamera;
    Entity* CurrentCameraOwner() { return CurrentCamera->Owner(); }

    GLBuffer<CameraData>* CamBuffer() { return &camBuffer; }

    void InitFrame()
    {
        camBuffer.ReplaceData(CurrentCamera->Data());
    }
};


#endif //IME_CAMERAMANAGER_H
