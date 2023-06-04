#include "Pigeon.h"
#include "Engine.h"

namespace mEngine
{
    Uint32 Pigeon::PigeonCount = 0;
    Uint8 Pigeon::m_PoopCount = 0;

    void mEngine::Pigeon::Update(float deltaTime)
    {
        Entity::Update(deltaTime);
        WallsCollisionCheck();
        m_AnimationData->Transform.TranslateXPosition(m_MoveDirection * m_MoveSpeed);

        m_Timer.Update();
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

    void Pigeon::Poop()
    {
        ++m_PoopCount;
        auto engine = mEngine::Engine::GetInstance();
        auto& activeEntities = engine->GetActiveEntities();
        const std::string& pooStr = std::to_string(m_PoopCount);

		if (engine->IsEntityActive("poo" + pooStr))
        {
            std::cerr << "Error, entity ID is taken, ID: poo" + pooStr << '\n';
        }
        activeEntities["poo" + pooStr] = new BirdPoo("poo" + pooStr, Math::Vec2D(GetPosition().x, GetPosition().y + 50));
    }

}