#include "FallingBirdPoo.h"
#include "common.h"
#include "Engine.h"

void mEngine::FallingBirdPoo::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	m_AnimationData->Transform.TranslateYPosition(m_MoveDirection * m_MoveSpeed);
}

void mEngine::FallingBirdPoo::Render()
{
	Entity::Render();
}

void mEngine::FallingBirdPoo::RenderFrame()
{
	Entity::RenderFrame();
}

void mEngine::FallingBirdPoo::Clean()
{
	Entity::Clean();
}
