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
		std::cout << "Performing A Task! Taking A Shit!\n";
        auto engine = mEngine::Engine::GetInstance();
        auto activeEntities = engine->GetActiveEntities();

		if (engine->IsEntityActive("poo" + PigeonCount))
        {
            std::cerr << "Error, entity ID is taken, ID: poo" + PigeonCount << '\n';
        }
        std::cout << "POOPING!\n";
        activeEntities["poo" + PigeonCount] = new BirdPoo("poo" + PigeonCount, { GetPosition().x,GetPosition().y + 50 });
    
    }

}