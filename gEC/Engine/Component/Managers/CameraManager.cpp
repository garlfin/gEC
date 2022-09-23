//
// Created by scion on 9/21/2022.
//

#include "CameraManager.h"
#include "Windowing/Window.h"

void CameraManager::InitFrame()
{
    camBuffer.ReplaceData(CurrentCamera->Data(), sizeof(CameraData));
}
