#include "Pigeon.h"

namespace mEngine
{
    Uint32 Pigeon::PigeonCount = 0;

    void mEngine::Pigeon::Update(float deltaTime)
    {
        Entity::Update(deltaTime);
    }

    void mEngine::Pigeon::Render()
    {
        Entity::Render();
    }

    void mEngine::Pigeon::RenderFrame()
    {
        Entity::RenderFrame();
    }

    void mEngine::Pigeon::Clean()
    {
        Entity::Clean();
    }

}