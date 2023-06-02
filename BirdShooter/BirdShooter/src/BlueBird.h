#pragma once
#include "Entity.h"

namespace mEngine
{
    class BlueBird : public Entity
    {
    public:
        BlueBird(const std::string& id, const Math::Vec2D& position) : Entity(CreateBlueBirdData(id, position))
        {
            BlueBirdCount++;
            m_Hittable = true;
        }

        void Update(float deltaTime) override;

        void Render() override;

        void RenderFrame() override;

        void Clean() override;

        static inline const Uint32 GetBlueBirdCount() { return BlueBirdCount; }


    private:
        AnimationData* CreateBlueBirdData(const std::string& id, const Math::Vec2D& position)
        {
            Math::Transform transform(position, 2.f, 0);
            return new AnimationData(id, "assets/BirdSprite.png", transform, 16, 16, 1, 0, 8, 80,SDL_FLIP_HORIZONTAL);
        }
        static Uint32 BlueBirdCount;
    };
 }
