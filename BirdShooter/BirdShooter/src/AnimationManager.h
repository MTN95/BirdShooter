#pragma once
#include "AnimationData.h"
#include <vector>

namespace mEngine
{
    class AnimationManager
    {
    public:
        static AnimationManager* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new AnimationManager();
        }

        void Update(float deltaTime);
        void RenderAnimations();
        void AddAnimation(AnimationData* animationData);
        void RemoveAnimation(AnimationData* animationData);
        void Clean();
    private:
        AnimationManager() {}
        static AnimationManager* s_Instance;

        std::vector<AnimationData*> m_Animations;
    };
}