//
// Created by scion on 9/8/2022.
//

#pragma once

#include <typeinfo>

#include "Component.h"
#include "../../Asset/Mesh/VAO.h"


class MeshRenderer : public Component {
private:
    VAO renderer;
public:
    MeshRenderer(Entity* owner);
    ~MeshRenderer();

    void OnLoad() override;

    void OnUpdate(double d) override;

    void OnRender(double d) override;

    void OnFree() override;
};

