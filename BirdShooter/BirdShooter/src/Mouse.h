#pragma once

#include <SDL_image.h>
#include "TextureManager.h"

namespace mEngine
{
	class Mouse
	{
	public:
		SDL_Texture* mouseTexture;
		SDL_Rect rect{};

		Mouse(SDL_Renderer* renderer) 
		{
			TextureManager::GetInstance()->LoadTexture("mouse", "assets/mouse3.png");
			mouseTexture = TextureManager::GetInstance()->GetTexture("mouse");

			rect.x = 0;
			rect.y = 0;
			rect.w = 50;
			rect.h = 50;
			SDL_ShowCursor(false);
		}

		void update() 
		{
			SDL_GetMouseState(&rect.x, &rect.y);
		}

		void render(SDL_Renderer* renderer) {
			int textureWidth = 500;
			int textureHeight = 500;
			SDL_QueryTexture(mouseTexture, nullptr, nullptr, &textureWidth, &textureHeight);

			rect.x = rect.x - textureWidth / 20;
			rect.y = rect.y - textureHeight/ 20;

			SDL_RenderCopy(renderer, mouseTexture, nullptr, &rect);
		}
	};


}