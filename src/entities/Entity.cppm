export module ModdersDream.Entity;

import ModdersDream.Renderer.Context;

export namespace ModdersDream {

class Entity {
public:
    Entity() {
        Initialize();
    }

    ~Entity() {
        Destroy();
    }

    // Called at construction
    virtual void Initialize() {}

    // Called at every tick
    virtual void Update(double deltaTime) {}

    // Called when needed to get rendered
    virtual void Render(ModdersDream::Renderer::Context rendererContext) {}

protected:
    // Called at deconstructor
    virtual void Destroy() {}
};

} // namespace ModdersDream
