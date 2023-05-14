#pragma once
#include "Entity.h"

namespace mEngine
{
	class FallingBirdPoo : public Entity
	{
	public:
		FallingBirdPoo(const std::string& id, const Math::Vec2D& position) 
			: Entity(CreateFallingPooData(id,position)) { }
		
		void Update(float deltaTime) override;

		void Render() override;

		void RenderFrame() override;

		void Clean() override;
	private:

		EntityData* CreateFallingPooData(const std::string& id, const Math::Vec2D& position)
		{
			Math::Transform transform(position, 1.0, 0);
			return new EntityData(id, "assets/fallingBirdpoop.png", transform, 32, 32, 0, 0, 4);
		}
	};
}