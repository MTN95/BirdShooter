#pragma once

#include "Entity.h"

namespace mEngine
{	
	class SplatBirdPoo : public Entity
	{
	public:
		SplatBirdPoo(const std::string& id, const Math::Vec2D& position)
			: Entity(CreateFallingPooData(id, position)) { }

		void Update(float deltaTime) override;

		void Render() override;

		void RenderFrame() override;

		void Clean() override;
	private:

		AnimationData* CreateFallingPooData(const std::string& id, const Math::Vec2D& position)
		{
			Math::Transform transform(position, 0.5, 0);
			return new AnimationData(id, "assets/hittingfloor_Birdpoop.png", transform, 64, 64, 0, 0, 8);
		}
	};
}