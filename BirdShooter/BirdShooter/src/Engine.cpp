#include "Engine.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "common.h"
#include "Vec2D.h"
#include <sstream>
#include "Entity.h"
#include "Timer.h"
#include <iostream>

namespace mEngine
{
    Engine* Engine::s_Instance = nullptr;

    bool Engine::Init(const char* title, bool fullscreen)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            std::cout << "Failed to initialize SDL! SDL_Error: " << SDL_GetError() << '\n';
            return false;
        }
        int window_flags = 0;
        if (fullscreen)
        {
            window_flags = SDL_WINDOW_FULLSCREEN;
        }

        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);

        if (m_Window == nullptr) {
            std::cout << "Failed to Create Window! SDL_Error: " << SDL_GetError() << '\n';
            return false;
        }

        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_Renderer == nullptr) {
            std::cout << "Failed to Create Renderer! SDL_Error: " << SDL_GetError() << '\n';
            return false;
        }

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
			return false;
		}

		if (TTF_Init() != 0)
		{
			std::cout << "SDL_ttf could not initialize!SDL_ttf Error : " << TTF_GetError() << std::endl;
			return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			// Error handling
			return false;
		}
    
        if (!LoadMedia())
        {
            std::cout << "Failed to Load Media!" << '\n';
            return false;
        }
        
        timer = new Timer();
        timer->setDurationInMins(10);

        countdownTime = 60;

        m_Mouse = new Mouse(m_Renderer);

        b = new BlueBird("b1",{400, 200});
        m_Entities.push_back(b);

        p = new Pigeon("p1",{600.f, 500.f});
        m_Entities.push_back(p);
        p2 = new Pigeon("p2",{200.f, 100.f});
        m_Entities.push_back(p2);


        m_IsRunning = true;
        return true;
    }

    void Engine::Clean()
    {
		for (auto entity : m_Entities) 
        {
            entity->Clean();
            delete entity;
		}

        TextureManager::GetInstance()->Clean();

        AudioManager::GetInstance()->Clean();

        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;

        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
        
        Mix_CloseAudio();
		TTF_Quit();
		IMG_Quit();
        SDL_Quit();
    }

    void Engine::Quit()
    {
        m_IsRunning = false;
    }

    void Engine::Update()
    {
        if (timer->GetRemainingSeconds() <= 0)
        {
            Quit();
        }

        m_Mouse->update();
                
        for (auto entity : m_Entities)
        {
            entity->Update(0);
            if (IsEntityHit(entity))
            {
                ++m_Score;
                AudioManager::GetInstance()->PlayAudio(birdSfx);
            }
        }
    }

    int Engine::ShowMenu(SDL_Surface* screen)
    {
        SDL_ShowCursor(true);

        //SDL_Surface* bgSurface = 

		int x, y;
		const int NumMenu = 2;
		const char* labels[NumMenu] = { "play", "quit" };
		SDL_Color color[2] = { {255, 255, 255}, {255, 0, 0} };
		bool selected[NumMenu] = { false, false };

		SDL_Surface* menus[NumMenu] =
		{
			TTF_RenderText_Solid(m_Fonts[0], labels[0], color[0]),
			TTF_RenderText_Solid(m_Fonts[0], labels[1], color[0])
		};

		SDL_Rect pos[NumMenu] =
		{
			{screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2, screen->clip_rect.h / 2 - menus[0]->clip_rect.h},
			{screen->clip_rect.w / 2 - menus[1]->clip_rect.w / 2, screen->clip_rect.h / 2 + menus[1]->clip_rect.h}
		};

        // Render the background textures
        for (int i = 1; i <= 6; ++i)
        {
            TextureManager::GetInstance()->Render("bg_" + std::to_string(i), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        // fills the screen black
        //SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 255, 255));

        // renders the background textures with the menu
        // Create a surface of the same size as the screen
        SDL_Surface* bgSurface = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);
        // Copy the texture pixels to the surface
        SDL_RenderReadPixels(m_Renderer, nullptr, SDL_PIXELFORMAT_RGBA32, bgSurface->pixels, bgSurface->pitch);
        // Set source and destination rectangles
        SDL_Rect dstRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        // Fill the entire screen with the surface pixels
        SDL_BlitSurface(bgSurface, &dstRect, screen, &dstRect);
        SDL_FreeSurface(bgSurface);

		SDL_Event event;
		while (true)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					for (auto& menu : menus)
					{
						SDL_FreeSurface(menu);
					}
					return 1;
				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					for (int i = 0; i < NumMenu; ++i)
					{
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
							y >= pos[i].y && y <= pos[i].y + pos[i].h) {
							if (!selected[i])
							{
								selected[i] = true;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(m_Fonts[0], labels[i], color[1]);
                                AudioManager::GetInstance()->PlayAudio(clickSfx);
                            }
						}
						else
						{
							if (selected[i])
							{
								selected[i] = false;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(m_Fonts[0], labels[i], color[0]);
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.button.x;
					y = event.button.y;
					for (int i = 0; i < NumMenu; ++i)
					{
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
							y >= pos[i].y && y <= pos[i].y + pos[i].h)
						{
							for (auto& menu : menus)
							{
								SDL_FreeSurface(menu);
							}
                            AudioManager::GetInstance()->PlayAudio(clickSfx);
							return i;
						}
					}
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						for (auto& menu : menus)
						{
							SDL_FreeSurface(menu);
						}
                        Quit();
						return 0;
					}
				}
			}
			for (int i = 0; i < NumMenu; ++i)
			{
				SDL_BlitSurface(menus[i], nullptr, screen, &pos[i]);
			}
			SDL_UpdateWindowSurface(m_Window);
		}
        return -1;
    }

    void Engine::Render()
    {
        PrepareScene();
        PresentScene();
    }

    void Engine::Events()
    {
        SDL_Event event;
        
        
        while (SDL_PollEvent(&event)) 
        {
            bool PressedOnce = event.type == SDL_KEYDOWN && event.key.repeat == 0;
        
            if (event.type == SDL_QUIT)
            {
                std::cout << "Quit\n";
                Quit();
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    AudioManager::GetInstance()->PlayAudio(shotSfx);
                }
            }
            //if (PressedOnce && event.key.keysym.sym == SDLK_s)
            //{
            //    if (timer.isStarted())
            //    {
            //        timer.stop();
            //    }
            //    else
            //    {
            //        timer.start();
            //    }
            //}
            //else if (PressedOnce && event.key.keysym.sym == SDLK_p)
            //{
            //    if (timer.isPaused())
            //    {
            //        timer.unpause();
            //    }
            //    else
            //    {
            //        timer.pause();
            //        std::cout << "Timer paused. Time elapsed: " << timer.getTicks() / 1000.f << " seconds\n";
            //    }
            //}            
        }
    }

    void Engine::RunEngine()
    {
        const int FPS = 60;
        const int frameDelay = 1000 / FPS;
        
        Uint32 frameStart;
        int frameTime;

        int i = ShowMenu(SDL_GetWindowSurface(m_Window));

        if (i == 1)
        {
            Quit();
        }

        SDL_ShowCursor(false);

        timer->start();
        
        while (IsRunning())
        {
            frameStart = SDL_GetTicks();
            
            Events();

            Update();
         
            Render();
            
            frameTime = SDL_GetTicks() - frameStart;
            
            if (frameDelay > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }

    bool Engine::LoadMedia()
    {
        // Background Textures    
        for (int i = 1; i <= 6; ++i)
        {
            if (!TextureManager::GetInstance()->LoadTexture("bg_" + std::to_string(i), "assets/Hills_Layer_" + std::to_string(i) + ".png"))
            {
                std::cout << "Failed to Load BackGround Images!\n";
                return false;
            }
        }

        if (!LoadFonts())
        {
            std::cout << "Failed to Load Fonts!\n";
        }
        if (!LoadSFX())
        {
            std::cout << "Failed to Load SFX!\n";
        }

        return true;
    }

    bool Engine::LoadFonts()
    {
        m_Fonts[0] = TTF_OpenFont("assets/fonts/pixel_font.ttf", 40);
        if (m_Fonts[0] == nullptr)
        {
            std::cout << "Failed to open font ! TTF_Error: " << TTF_GetError() << std::endl;
            return false;
        }
        m_Fonts[1] = TTF_OpenFont("assets/fonts/pixel_font.ttf", 20);
        if (m_Fonts[1] == nullptr)
        {
            std::cout << "Failed to open font ! TTF_Error: " << TTF_GetError() << std::endl;
            return false;
        }
        return true;
    }

    bool Engine::LoadSFX()
    {
        shotSfx = AudioManager::GetInstance()->LoadAudio("shotSfx", "assets/sfx/shot.wav");
        if (shotSfx == nullptr)
        {
            std::cout << "Failed to load audio " << "shotSfx" << " Mix_Error: " << Mix_GetError() << '\n';
            return false;
        }

        birdSfx = AudioManager::GetInstance()->LoadAudio("birdSfx", "assets/sfx/BirdSquake.wav");
        if (birdSfx == nullptr)
        {
            std::cout << "Failed to load audio " << "birdSfx" << " Mix_Error: " << Mix_GetError() << '\n';
            return false;
        }

        clickSfx = AudioManager::GetInstance()->LoadAudio("clickSfx", "assets/sfx/click.wav");
        if (birdSfx == nullptr)
        {
            std::cout << "Failed to load audio " << "birdSfx" << " Mix_Error: " << Mix_GetError() << '\n';
            return false;
        }
        
        return true;
    }

    void Engine::PrepareScene()
    {
        SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
        SDL_RenderClear(m_Renderer);
    }

	void Engine::PresentScene()
	{
		// Render background
		for (int i = 1; i <= 6; ++i)
		{
			TextureManager::GetInstance()->Render("bg_" + std::to_string(i), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		// Render score
		TextureManager::GetInstance()->RenderText("Score:", 25, 25, m_Fonts[1], { 0, 180, 0, 255 }, 2, m_Score);

		// Render remaining time
		std::string remainingTimeString = timer->LogCountDown();
		TextureManager::GetInstance()->RenderText(remainingTimeString, 25, 225, m_Fonts[1], { 0, 180, 0, 255 }, 2);

		// Render entities
		for (auto entity : m_Entities)
		{
			entity->RenderFrame();
		}

		// Render mouse
		m_Mouse->render(m_Renderer);

		// Present scene
		SDL_RenderPresent(m_Renderer);
	}

    bool Engine::isMouseOverEntity(Entity* entity, int mouseX, int mouseY)
	{
		// Calculate the rectangular bounds of the entity
		SDL_Rect entityRect = {
			static_cast<int>(entity->GetPosition().x),
			static_cast<int>(entity->GetPosition().y),
			static_cast<int>(entity->GetWidth() * entity->GetScale()),
			static_cast<int>(entity->GetHeight() * entity->GetScale())
		};

		// Check if the mouse coordinates are inside the entity's bounds
		return mouseX >= entityRect.x && mouseX <= entityRect.x + entityRect.w &&
			mouseY >= entityRect.y && mouseY <= entityRect.y + entityRect.h;
	}

    bool Engine::IsEntityHit(Entity* entity)
	{
        bool success = false;
		int MouseX, MouseY;
		Uint32 mouseState = SDL_GetMouseState(&MouseX, &MouseY);
        if (entity != nullptr)
        {
		    if (isMouseOverEntity(entity, MouseX, MouseY))
		    {
			    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) 
                {
                    timer->AddSeconds(10);
				    // sfx + fx + death anim ?
                    entity->Clean();
					// remove entity from vector
					m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entity), m_Entities.end());
                    success = true;
                }
		    }
        }
        return success;
    }
}