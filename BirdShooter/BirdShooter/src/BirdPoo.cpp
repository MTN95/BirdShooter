#include "BirdPoo.h"
#include "common.h"
#include "Engine.h"
#include "AudioManager.h"

namespace mEngine
{

	void mEngine::BirdPoo::Update(float deltaTime)
	{
		Entity::Update(deltaTime);

		m_AnimationData->Transform.TranslateYPosition(m_MoveDirection * m_MoveSpeed);
	}

	void mEngine::BirdPoo::Render()
	{
		Entity::Render();
	}

	void mEngine::BirdPoo::RenderFrame()
	{
		Entity::RenderFrame();
	}

	void mEngine::BirdPoo::Clean()
	{
		Entity::Clean();
	}

	void BirdPoo::HasCollided(std::map<std::string, Entity*>& activeEntities, Mix_Chunk* hitSFX)
	{
		auto engine = mEngine::Engine::Getinstance();
		engine->AddEntityToRemove(GetID());
		activeEntities[GetID()]->Clean();

		SetHasBeenHit(true);
		AudioManager::GetInstance()->PlayAudio(hitSFX);

		auto it = activeEntities.find("falling poo");
		if (it == activeEntities.end())
		{
			std::cout << "Error: 'falling poo' entity not found in activeEntities map!\n";
		}

		BirdPoo* fallingPoo = dynamic_cast<BirdPoo*>(it->second);
		if (fallingPoo == nullptr)
		{
			std::cout << "Error: Entity is not of type BirdPoo!\n";
		}

		fallingPoo = new BirdPoo(GetID(),GetPosition(),true);

	}
}