#pragma once

#include "IObject.h"
#include "AnimationData.h"

namespace mEngine
{


	class Entity : public IObject
	{
	public:
		Entity() = default;
		Entity(AnimationData* data);

		void Log()
		{
			std::cout << m_AnimationData->TextureID << '\n';
			m_AnimationData->Transform.getPosition().Log("POS:");
			std::cout << "Scale: " << m_AnimationData->Transform.getScale() << '\n';
			std::cout << "Rotation: " << m_AnimationData->Transform.getRotation() << '\n';
			std::cout << "Width: " << m_AnimationData->Width << ' ' << "Height: " << m_AnimationData->Height << '\n';
		}

		virtual ~Entity();

		void Update(float deltaTime) override;
		void Render() override;
		void RenderFrame() override;
		void Clean() override;
		void WallsCollisionCheck();
		AnimationData* SetAnimationData(AnimationData* data);

		inline const Math::Vec2D GetPosition() const { return m_AnimationData->Transform.getPosition(); }
		inline const float& GetScale() const { return m_AnimationData->Transform.getScale(); }
		inline const double& GetRotation() const { return m_AnimationData->Transform.getRotation(); }
		inline const float& GetWidth() const { return m_AnimationData->Width; }
		inline const float& GetHeight() const { return m_AnimationData->Height; }
		inline const std::string& GetID() const { return m_AnimationData->TextureID; }

		inline const unsigned int GetEntityCount() { return EntityCount; }

		inline const bool& IsHittable() const { return m_Hittable; }

		inline bool& GetHasBeenHit() { return m_HasBeenHit; }
		inline void SetHasBeenHit(bool b) { m_HasBeenHit = b; }

	protected:
		AnimationData* m_AnimationData;
		
		int m_AnimSpeed;
		float m_MoveDirection;
		float m_MoveSpeed;
		
		bool m_Hittable;
		bool m_HasBeenHit;

		unsigned int EntityCount = 0;
	};
}