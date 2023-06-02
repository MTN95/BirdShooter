#include "Entity.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "common.h"

namespace mEngine 
{
	mEngine::Entity::Entity(AnimationData* data)
	{
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

	void Entity::SetAnimationData(AnimationData* animData)
	{
		m_AnimationData = animData;
	}

}