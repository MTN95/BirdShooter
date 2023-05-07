#include "Entity.h"
#include "TextureManager.h"
#include "common.h"

namespace mEngine 
{
	mEngine::Entity::Entity(EntityData* data)
		: m_TextureID(data->TextureID), m_Transform(data->Transform),
		m_Width(data->Width), m_Height(data->Height), m_Flip(data->Flip)
	{
		m_Row = data->Row;
		m_Frame = data->Frame;
		m_FrameCount = data->FrameCount;
		m_AnimSpeed = 80;
		m_MoveDirection = 1.f;
		m_MoveSpeed = 3.f;
		if(!TextureManager::GetInstance()->LoadTexture(m_TextureID,data->Path))
		{
			std::cout << "Failed to load entity texture!\n" << '\n';
		}
		// Log();
		EntityCount++;
	}

	mEngine::Entity::~Entity()
	{

	}
	void mEngine::Entity::Update(float deltaTime)
	{
		// Calculate current frame based on animation speed
		m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;

		if (m_Transform.getPosition().x >= SCREEN_WIDTH - m_Width)
		{
			m_MoveDirection *= -1.f;
			if (m_Flip == SDL_FLIP_HORIZONTAL)
			{
				m_Flip = SDL_FLIP_NONE;
			}
			else if (m_Flip == SDL_FLIP_NONE)
			{
				m_Flip = SDL_FLIP_HORIZONTAL;
			}
		}
		if (m_Transform.getPosition().x <= 0)
		{
			m_MoveDirection *= -1.f;
			if (m_Flip == SDL_FLIP_HORIZONTAL)
			{
				m_Flip = SDL_FLIP_NONE;
			}
			else if (m_Flip == SDL_FLIP_NONE)
			{
				m_Flip = SDL_FLIP_HORIZONTAL;
			}
		}
		
		m_Transform.TranslateXPosition(m_MoveDirection * m_MoveSpeed);
	}

	void mEngine::Entity::Render()
	{
		TextureManager::GetInstance()->Render(m_TextureID, m_Transform.getPosition().x,m_Transform.getPosition().y, m_Width, m_Height, m_Transform.getScale(),m_Flip);
	}
	void mEngine::Entity::RenderFrame()
	{
		TextureManager::GetInstance()->RenderFrame(m_TextureID, m_Transform.getPosition().x, m_Transform.getPosition().y, m_Width, m_Height, m_Row, m_Frame,m_Transform.getScale(), m_Flip);
	}

	void mEngine::Entity::Clean()
	{
		TextureManager::GetInstance()->CleanTexture(m_TextureID);
	}

}