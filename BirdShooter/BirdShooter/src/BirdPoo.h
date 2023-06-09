#pragma once
#include "Entity.h"

namespace mEngine
{
	class BirdPoo : public Entity
	{
	public:
		BirdPoo(const std::string& id, const Math::Vec2D& position, bool isSplatPoo = false)
			: Entity ((isSplatPoo) ? CreateSplatPooData(id, position) : CreateFallingPooData(id, position))
		{
			m_EntityType = EntityType::Poo;
		}

		void Update(float deltaTime) override;

		void Render() override;

		void RenderFrame() override;

		void Clean() override;

		void HasCollided(std::map<std::string, Entity*>& activeEntities, Mix_Chunk* hitSFX, BirdPoo* collidedPoo);

		bool IsColliding();

		AnimationData* CreateFallingPooData(const std::string& id, const Math::Vec2D& position)
		{
			Math::Transform transform(position, 1.0, 0);
			return new AnimationData(id, "assets/fallingBirdpoop.png", transform, 32, 32, 0, 0, 4, 80);
		}
		AnimationData* CreateSplatPooData(const std::string& id, const Math::Vec2D& position)
		{
			Math::Transform transform(position, 0.5, 0);
			return new AnimationData(id, "assets/hittingfloor_Birdpoop.png", transform, 64, 64, 0, 0, 8, 80,false);
		}

		BirdPoo() = delete;

		bool operator==(const BirdPoo& other) const = delete;
	};
}