export module ModdersDream.ObjectEntity;

import ModdersDream.Renderer.Context;
import ModdersDream.Entity;

using namespace ModdersDream;

export namespace ModdersDream {

class ObjectEntity : public Entity {
public:
    virtual void Render(ModdersDream::Renderer::Context rendererContext) override {
    }
};

} // namespace ModdersDream
