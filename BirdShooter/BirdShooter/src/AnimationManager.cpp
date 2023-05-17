#include "AnimationManager.h"
#include "TextureManager.h"

namespace mEngine
{
	AnimationManager* AnimationManager::s_Instance = nullptr;
	void AnimationManager::Update(float deltaTime)
	{
		for (auto animationData : m_Animations)
		{
			// Update each animation
			animationData->Frame = (SDL_GetTicks() / animationData->AnimSpeed) % animationData->FrameCount;

			// Check if the animation has reached the end
			if (animationData->Frame == animationData->FrameCount - 1)
			{
				if (!animationData->Loop)
				{
					// Animation reached the end and should be terminated
					// Remove the animation from the list
					RemoveAnimation(animationData);

					// Optionally, you can delete the animation object if it's dynamically allocated
					delete animationData;
				}
			}
		}
	}
	void AnimationManager::RenderAnimations()
	{
		for (auto animationData : m_Animations)
		{
			// Render each animation
			TextureManager::GetInstance()->RenderFrame(animationData->TextureID, animationData->Transform.getPosition().x,
				animationData->Transform.getPosition().y, animationData->Width, animationData->Height, animationData->Row,
				animationData->Frame, animationData->Transform.getScale(), animationData->Flip);
		}
	}

	void AnimationManager::Clean()
	{
		// Clean up the animations
		for (auto animationData : m_Animations)
		{
			// Optionally, you can delete the animation object if it's dynamically allocated
			delete animationData;
		}

		// Clear the container
		m_Animations.clear();
	}

	void AnimationManager::AddAnimation(AnimationData* animationData)
	{
		m_Animations.push_back(animationData);
	}

	void AnimationManager::RemoveAnimation(AnimationData* animationData)
	{
		// Find and remove the animation from the container
		auto it = std::find(m_Animations.begin(), m_Animations.end(), animationData);
		if (it != m_Animations.end())
			m_Animations.erase(it);
	}

}