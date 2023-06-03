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

		//if (IsColliding())
		//{
		//	std::cout << "Poo Colliding!\n";
		//}
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

		SetHasBeenHit(true);
		AudioManager::GetInstance()->PlayAudio(hitSFX);
		fallingPoo = new BirdPoo(GetID(),GetPosition(),true);

	}

	bool BirdPoo::IsColliding()
	{
		auto engine = mEngine::Engine::GetInstance();
		auto& activeEntities = engine->GetActiveEntities();
		auto& entitiesToRemove = engine->GetEntitiesToRemove();

		auto fallingPooIterator = activeEntities.find(GetID());
		if (fallingPooIterator != activeEntities.end())
		{
			auto fallingPoo = fallingPooIterator->second;
			auto pooPos = fallingPoo->GetPosition();
			BirdPoo* birdPooPtr = dynamic_cast<BirdPoo*>(fallingPoo);
			if (birdPooPtr == nullptr)
			{
				std::cout << "birdPooPtr is nullptr!\n";
				return false;
			}

			// Check if colliding with house / animals / trees / whatever
			if (pooPos.y >= SCREEN_HEIGHT - (SCREEN_HEIGHT / 2.0))
			{
				std::cout << "bird_Poo is HIT MAN!\n";
				if (!fallingPoo->GetHasBeenHit())
				{
					birdPooPtr->HasCollided(activeEntities, engine->GetPooSFX());
					entitiesToRemove.emplace_back(GetID());
					return true;
				}
			}
		}
		return false;
	}

	
}