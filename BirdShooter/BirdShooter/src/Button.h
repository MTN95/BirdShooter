#pragma once

#include "Mouse.h"

namespace mEngine
{
	class Button {
	public:
		SDL_Texture* buttonTexture;
		SDL_Rect srect;
		SDL_Rect drect;
		bool isSelected = false;
		Button();
		virtual ~Button();

		void setTexture(SDL_Texture* newTexture);
		void update(Mouse&);
		void render(SDL_Renderer* renderer);

	};

}
