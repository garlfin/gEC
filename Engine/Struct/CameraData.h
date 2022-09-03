//
// Created by scion on 9/2/2022.
//

#ifndef IME_CAMERADATA_H
#define IME_CAMERADATA_H

#include <glm/mat4x4.hpp>

struct alignas(16) CameraData  {
    glm::mat4 View;
    glm::mat4 Projection;
    glm::vec3 CameraPos;
    glm::vec4 OtherData; // FOV, CLIP_NEAR, CLIP_FAR, ASPECT
};

#endif //IME_CAMERADATA_H
