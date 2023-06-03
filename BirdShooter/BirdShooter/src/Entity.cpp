#include "Entity.h"
#include "Engine.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "common.h"

namespace mEngine 
{
	mEngine::Entity::Entity(AnimationData* data)
	{
		m_EntityType = EntityType::None;
		m_AnimationData = data;
		m_HasBeenHit = false;
		// m_AnimSpeed = 80;
		m_MoveDirection = 1.f;
		m_MoveSpeed = 3.f;
		m_Hittable = false;
		if(!TextureManager::GetInstance()->LoadTexture(m_AnimationData->TextureID,data->Path))
		{
			std::cout << "Failed to load entity texture!\n" << '\n';
		}
		// Log();
		EntityCount++;
		AnimationManager::GetInstance()->AddAnimation(m_AnimationData);
	}

	mEngine::Entity::~Entity() = default;

	void mEngine::Entity::Update(float deltaTime)
	{
		if (GetEntityType() == EntityType::Poo)
		{
			BirdPoo* PooPtr = dynamic_cast<BirdPoo*>(this);
			if (PooPtr == nullptr)
			{
				std::cerr << "PooPtr is nullptr!\n";
			}
			PooPtr->IsColliding();
		}
		
	}

	void mEngine::Entity::Render()
	{
		RenderFrame();
	}
	void mEngine::Entity::RenderFrame()
	{
	}

	void mEngine::Entity::Clean()
	{
		TextureManager::GetInstance()->CleanTexture(m_AnimationData->TextureID);
	}

	void Entity::WallsCollisionCheck()
	{
		if (m_AnimationData->Transform.getPosition().x >= SCREEN_WIDTH - m_AnimationData->Width)
		{
			m_MoveDirection *= -1.f;
			if (m_AnimationData->Flip == SDL_FLIP_HORIZONTAL)
			{
				m_AnimationData->Flip = SDL_FLIP_NONE;
			}
			else if (m_AnimationData->Flip == SDL_FLIP_NONE)
			{
				m_AnimationData->Flip = SDL_FLIP_HORIZONTAL;
			}
		}
		if (m_AnimationData->Transform.getPosition().x <= 0)
		{
			m_MoveDirection *= -1.f;
			if (m_AnimationData->Flip == SDL_FLIP_HORIZONTAL)
			{
				m_AnimationData->Flip = SDL_FLIP_NONE;
			}
			else if (m_AnimationData->Flip == SDL_FLIP_NONE)
			{
				m_AnimationData->Flip = SDL_FLIP_HORIZONTAL;
			}
		}
	}

	void Entity::CheckIfHit()
	{
		auto engine = mEngine::Engine::GetInstance();
		auto activeEntities = engine->GetActiveEntities();
		auto entitiesToRemove = engine->GetEntitiesToRemove();
		auto pooSFX = engine->GetPooSFX();


		auto fallingPooIterator = activeEntities.find("falling poo");
		if (fallingPooIterator != activeEntities.end())
		{
			auto fallingPoo = fallingPooIterator->second;
			auto pooPos = fallingPoo->GetPosition();
			BirdPoo* birdPooPtr = dynamic_cast<BirdPoo*>(fallingPoo);
			//check if colliding with house / animals / trees / whatever
			if (pooPos.y >= SCREEN_HEIGHT - (SCREEN_HEIGHT / 2.0))
			{
				if (!fallingPoo->GetHasBeenHit())
				{
					BirdPoo* birdPooPtr = dynamic_cast<BirdPoo*>(fallingPoo);
					if (birdPooPtr == nullptr)
					{
						std::cout << "birdPooPtr is nullptr!\n";
					}

					birdPooPtr->HasCollided(activeEntities, pooSFX);
					entitiesToRemove.emplace_back("falling poo");

				}
			}
		}
	}


}