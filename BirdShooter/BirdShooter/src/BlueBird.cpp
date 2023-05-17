#include "BlueBird.h"

namespace mEngine
{
    Uint32 BlueBird::BlueBirdCount = 0;

    void mEngine::BlueBird::Update(float deltaTime)
    {
        Entity::Update(deltaTime);
        WallsCollisionCheck();
        m_AnimationData->Transform.TranslateXPosition(m_MoveDirection * m_MoveSpeed);
    }

    void mEngine::BlueBird::Render()
    {
        Entity::Render();
    }

    void mEngine::BlueBird::RenderFrame()
    {
        Entity::RenderFrame();
    }

    void mEngine::BlueBird::Clean()
    {
        Entity::Clean();
    }

}