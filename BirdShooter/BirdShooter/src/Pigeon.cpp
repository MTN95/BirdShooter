#include "Pigeon.h"
#include "Engine.h"

namespace mEngine
{
    Uint32 Pigeon::PigeonCount = 0;

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
        std::cout << "Performing A Task! Pigeon Is Taking A Shit!\n";

        ++m_PoopCount;
        auto engine = mEngine::Engine::GetInstance();
        auto& activeEntities = engine->GetActiveEntities();

		if (engine->IsEntityActive("poo" + PigeonCount))
        {
            std::cerr << "Error, entity ID is taken, ID: poo" + m_PoopCount << '\n';
        }
        activeEntities["poo" + m_PoopCount] = new BirdPoo("poo" + m_PoopCount, Math::Vec2D(GetPosition().x, GetPosition().y + 50));
    }

}