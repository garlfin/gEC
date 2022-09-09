//
// Created by scion on 9/8/2022.
//

#ifndef IME_MESHRENDERER_H
#define IME_MESHRENDERER_H

#include <typeinfo>

#include "Component.h"
#include "../Asset/Mesh/VAO.h"


class MeshRenderer : public Component {
private:
    VAO renderer;
protected:
    void OnFree() override;
public:
    MeshRenderer(Entity* owner);
    void OnLoad() override;

    void OnUpdate(double d) override;

    void OnRender(double d) override;
};


#endif //IME_MESHRENDERER_H
