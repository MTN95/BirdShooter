#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <memory>
#include "BirdPoo.h"
#include "Pigeon.h"
#include "Mouse.h"
#include "Timer.h"
#include <map>
#include <vector>


namespace mEngine
{

	class Engine
	{
	public:
		
		static inline Engine* GetInstance()
		{
			return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
		}

		bool Init(const char* title, bool fullscreen);
		void Clean();
		void Quit();
		void Update(float deltaTime);

		void UpdateEntities(float deltaTime);

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

		inline std::map<std::string, Entity*>& GetActiveEntities() { return m_ActiveEntitiesMap; }
		inline std::vector<std::string>& GetEntitiesToRemove() { return m_EntitiesToRemove; }
		inline Entity* GetActiveEntity(const std::string& id);
		inline void AddEntityToRemove(const std::string& id) { m_EntitiesToRemove.emplace_back(id); }
		bool IsEntityActive(const std::string& entityId);
		

		inline Mix_Chunk* GetPooSFX() { return pooSplatSfx; }

	private:
		Engine() : m_Window(nullptr), m_Renderer(nullptr), m_IsRunning(false)
		{
			timer = nullptr;
			countdownTime = 0;
			m_Mouse = nullptr;
			m_Fonts[0] = nullptr;
			m_Fonts[1] = nullptr;
			m_Score = 0;
			shotSfx = nullptr;
			birdSfx = nullptr;
			clickSfx = nullptr;
			pooSplatSfx = nullptr;
		}

		static Engine* s_Instance;

		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;

		Timer* timer;
		int countdownTime;

		bool m_IsRunning;

		TTF_Font* m_Fonts[2];

		Mix_Chunk* shotSfx;
		Mix_Chunk* birdSfx;
		Mix_Chunk* clickSfx;
		Mix_Chunk* pooSplatSfx;

		Mouse* m_Mouse;
		std::vector<std::string> m_EntitiesToRemove;
		std::map<std::string,Entity*> m_ActiveEntitiesMap;
		int m_Score;
	};
}
