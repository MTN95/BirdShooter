#include "Entity.h"
#include "TextureManager.h"
#include "common.h"

namespace mEngine 
{
	mEngine::Entity::Entity(AnimationData* data)
	{
		m_AnimationData = SetAnimationData(data);
		m_HasBeenHit = false;
		m_AnimSpeed = 80;
		m_MoveDirection = 1.f;
		m_MoveSpeed = 3.f;
		m_Hittable = false;
		if(!TextureManager::GetInstance()->LoadTexture(m_AnimationData->TextureID,data->Path))
		{
			std::cout << "Failed to load entity texture!\n" << '\n';
		}
		// Log();
		EntityCount++;
	}

	mEngine::Entity::~Entity() = default;

	void mEngine::Entity::Update(float deltaTime)
	{
		// Calculate current frame based on animation speed
		m_AnimationData->Frame = (SDL_GetTicks() / m_AnimSpeed) % m_AnimationData->FrameCount;

	}

	void mEngine::Entity::Render()
	{
		RenderFrame();
	}
	void mEngine::Entity::RenderFrame()
	{
		TextureManager::GetInstance()->RenderFrame(m_AnimationData->TextureID, m_AnimationData->Transform.getPosition().x,
			m_AnimationData->Transform.getPosition().y, m_AnimationData->Width, m_AnimationData->Height, m_AnimationData->Row, 
			m_AnimationData->Frame, m_AnimationData->Transform.getScale(), m_AnimationData->Flip);
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

	AnimationData* Entity::SetAnimationData(AnimationData* data)
	{
		AnimationData* newData = data;

		return newData;
	}

}