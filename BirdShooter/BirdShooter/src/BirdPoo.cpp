#include "BirdPoo.h"
#include "common.h"
#include "Engine.h"
#include "AudioManager.h"

namespace mEngine
{

	void BirdPoo::Update(float deltaTime)
	{
		Entity::Update(deltaTime);
		m_AnimationData->Transform.TranslateYPosition(m_MoveDirection * m_MoveSpeed);
		IsColliding();

	}

	void BirdPoo::Render()
	{
		Entity::Render();
	}

	void BirdPoo::RenderFrame()
	{
		Entity::RenderFrame();
	}

	void BirdPoo::Clean()
	{
		Entity::Clean();
	}


	void BirdPoo::HasCollided(std::map<std::string, Entity*>& activeEntities, Mix_Chunk* hitSFX, BirdPoo* collidedPoo)
	{
		if (collidedPoo == nullptr)
		{
			std::cout << "Error: Entity is not of type BirdPoo!\n";
		}

		SetIsHit(true);
		AudioManager::GetInstance()->PlayAudio(hitSFX);
		collidedPoo = new BirdPoo(GetID(),GetPosition(),true);

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
				std::cout << birdPooPtr->GetID() << " is HIT!\n";
				if (!fallingPoo->GetIsHit())
				{
					birdPooPtr->HasCollided(activeEntities, engine->GetPooSFX(),this);
					entitiesToRemove.emplace_back(GetID());
					return true;
				}
			}
		}
		return false;
	}

	
}