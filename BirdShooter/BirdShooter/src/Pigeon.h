#pragma once
#include "Entity.h"

namespace mEngine
{
    class Pigeon : public Entity
    {
    public:
        Pigeon(const std::string& id,const Math::Vec2D& position) : Entity(CreatePigeonData(id,position))
        {
            PigeonCount += 1;
            
            m_Hittable = true;
        }

        void Update(float deltaTime) override;
        
        void Render() override;
        
        void RenderFrame() override;
        
        void Clean() override;

        static inline const Uint32 GetPigeonCount() { return PigeonCount; }
       

    private:
        AnimationData* CreatePigeonData(const std::string& id,const Math::Vec2D& position)
        {
            Math::Transform transform(position, 1.f, 0);
            return new AnimationData(id, "assets/pigeon_fiy-Sheet.png", transform, 32, 32, 0, 0, 7,80);
        }
        static Uint32 PigeonCount;
        
    };
}
