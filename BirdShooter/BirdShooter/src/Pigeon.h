#pragma once
#include "Entity.h"
#include "Timer.h"

namespace mEngine
{
    class Pigeon : public Entity
    {
    public:
        Pigeon(const std::string& id,const Math::Vec2D& position) : Entity(CreatePigeonData(id,position))
        {
            m_EntityType = EntityType::Pigeon;
            ++PigeonCount;
            
            m_Hittable = true;
            m_PoopCount = 0;
			// Set the timer task to be performed every 10 seconds
			m_Timer.setTask([this]() {
				// Perform the desired action
                Poop();
				}, 6);
			// Start the timer
			m_Timer.start();
        }

        void Update(float deltaTime) override;
        
        void Render() override;
        
        void RenderFrame() override;
        
        void Clean() override;

        void Poop();

        static inline const Uint32 GetPigeonCount() { return PigeonCount; }
       

    private:
        AnimationData* CreatePigeonData(const std::string& id,const Math::Vec2D& position)
        {
            Math::Transform transform(position, 1.f, 0);
            return new AnimationData(id, "assets/pigeon_fiy-Sheet.png", transform, 32, 32, 0, 0, 7,80);
        }
        static Uint32 PigeonCount;

        Timer m_Timer;
        
        int m_PoopCount;
    };
}
