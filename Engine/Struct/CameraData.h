//
// Created by scion on 9/2/2022.
//

#pragma once

#include <glm/mat4x4.hpp>

struct CameraData  {
    glm::mat4 View;
    glm::mat4 Projection;
    glm::vec3 CameraPos;
private:
    float _pad;
public:
    glm::vec4 OtherData; // FOV, CLIP_NEAR, CLIP_FAR, ASPECT
};

