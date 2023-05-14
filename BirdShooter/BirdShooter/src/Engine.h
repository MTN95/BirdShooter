#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <memory>
#include "BlueBird.h"
#include "FallingBirdPoo.h"
#include "SplatBirdPoo.h"
#include "Pigeon.h"
#include "Mouse.h"
#include "Timer.h"
#include <vector>


namespace mEngine
{

	class Engine
	{
	public:
		
		static inline Engine* Getinstance()
		{
			return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
		}

		bool Init(const char* title, bool fullscreen);
		void Clean();
		void Quit();
		void Update(float deltaTime);

		int ShowMenu(SDL_Surface* screen);

		void Render();
		void Events();
		void RunEngine();

		bool LoadMedia();
		bool LoadFonts();
		bool LoadSFX();
		void PrepareScene();
		void PresentScene();

		inline bool IsRunning() { return m_IsRunning; }

		inline SDL_Renderer* GetRenderer() { return m_Renderer; }

		bool isMouseOverEntity(Entity* entity, int mouseX, int mouseY);
		bool IsEntityHit(Entity* entity);

		inline TTF_Font** GetFonts() { return m_Fonts; }

		inline SDL_Window* GetWindow() 
		{
			return m_Window; 
		}

	private:
		Engine() : m_Window(nullptr), m_Renderer(nullptr), m_IsRunning(false)
		{
			timer = nullptr;
			countdownTime = 0;
			p = nullptr;
			p2 = nullptr;
			b = nullptr;
			fallingPoo = nullptr;
			splatPoo = nullptr;
			m_Mouse = nullptr;
			m_Fonts[0] = nullptr;
			m_Fonts[1] = nullptr;
			m_Score = 0;
			shotSfx = nullptr;
			birdSfx = nullptr;
			clickSfx = nullptr;
		}

		static Engine* s_Instance;

		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;

		Timer* timer;
		int countdownTime;

		//mEngine::Entity* player;
		Pigeon* p; 
		Pigeon* p2; 
		BlueBird* b; 
		FallingBirdPoo* fallingPoo;
		SplatBirdPoo* splatPoo;

		bool m_IsRunning;

		TTF_Font* m_Fonts[2];

		Mix_Chunk* shotSfx;
		Mix_Chunk* birdSfx;
		Mix_Chunk* clickSfx;

		Mouse* m_Mouse;
		std::vector<Entity*> m_ActiveEntities;
		int m_Score;
	};
}
