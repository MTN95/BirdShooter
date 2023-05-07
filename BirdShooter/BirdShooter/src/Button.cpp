#include "Button.h"

namespace mEngine
{
	Button::Button() {

		buttonTexture = nullptr;
		srect.h = 100;
		srect.w = 400;
		srect.x = 0;

		drect.h = 75;
		drect.w = 300;


	}

	void Button::setTexture(SDL_Texture* newTexture)
	{
		buttonTexture = newTexture;
	}

	Button::~Button() {
	}

	void Button::update(Mouse& mouse) {

		if (SDL_HasIntersection(&mouse.rect, &drect)) {
			isSelected = true;
			srect.x = 400;
		}
		else {
			isSelected = false;
			srect.x = 0;
		}
	}

	void Button::render(SDL_Renderer* renderer) {
		SDL_RenderCopy(renderer, buttonTexture, &srect, &drect);
	}
}
