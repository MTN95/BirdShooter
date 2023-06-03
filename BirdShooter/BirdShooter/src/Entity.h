#pragma once

#include "IObject.h"
#include "AnimationData.h"
#include <SDL_mixer.h>
#include <string>
#include <map>

namespace mEngine
{
	enum class EntityType
	{
		None,
		Static,
		Pigeon,
		BlueBird,
		Poo
	};

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
		void CheckIfHit();

		inline const Math::Vec2D GetPosition() const { return m_AnimationData->Transform.getPosition(); }
		inline const float& GetScale() const { return m_AnimationData->Transform.getScale(); }
		inline const double& GetRotation() const { return m_AnimationData->Transform.getRotation(); }
		inline const float& GetWidth() const { return m_AnimationData->Width; }
		inline const float& GetHeight() const { return m_AnimationData->Height; }
		inline const std::string& GetID() const { return m_AnimationData->TextureID; }

		inline const unsigned int GetEntityCount() { return EntityCount; }

		inline const bool& IsHittable() const { return m_Hittable; }

		inline bool& GetIsHit() { return m_IsHit; }
		inline void SetIsHit(bool b) { m_IsHit = b; }

		inline EntityType SetEntityType(EntityType newType) { return m_EntityType = newType; }
		inline EntityType GetEntityType() { return m_EntityType; }

	protected:
		AnimationData* m_AnimationData;
		
		EntityType m_EntityType;

		float m_MoveDirection;
		float m_MoveSpeed;
		
		bool m_Hittable;
		bool m_IsHit;

		unsigned int EntityCount = 0;
	};
}