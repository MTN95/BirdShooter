#include "TextureManager.h"
#include "Engine.h"
#include <SDL.h>
#include <iostream>

namespace mEngine
{
    TextureManager* TextureManager::s_Instance = nullptr;

    bool TextureManager::LoadTexture(std::string id, std::string path)
    {
        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == nullptr)
        {
            std::cout << "Unable to load image! SDL_image Error: " << IMG_GetError();
            return false;
        }

        //Create texture from surface pixels
        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(Engine::Getinstance()->GetRenderer(), loadedSurface);
        if (newTexture == nullptr)
        {
            std::cout << "Unable to create texture from loadedSurface! SDL Error: " << SDL_GetError();
            return false;
        }

        SDL_FreeSurface(loadedSurface);
        m_TextureMap[id] = newTexture;

        return true;
    }

    SDL_Surface* TextureManager::CreateTextSurface(const std::string& text, TTF_Font* font, SDL_Color color)
	{
		return TTF_RenderText_Solid(font, text.c_str(), color);
	}

    void TextureManager::CleanTexture(std::string id)
    {
        SDL_DestroyTexture(m_TextureMap[id]);
        m_TextureMap.erase(id);
        m_TextureMap[id] = nullptr;
    }

    void TextureManager::Clean()
    {
		for (auto& texture : m_TextureMap)
		{
			SDL_DestroyTexture(texture.second);
		}
        m_TextureMap.clear();
    }

    void TextureManager::Render(std::string id, float x, float y, float width, float height, float scale, SDL_RendererFlip flip)
    {
        // Set rendering space and render to screen
        SDL_Rect srcRect = 
        { 
            0, 
            0, 
            static_cast<int>(width), 
            static_cast<int>(height)
        };
        SDL_FRect dstRect = { x, y, width * scale, height * scale};

        // Render to screen
        SDL_RenderCopyExF(Engine::Getinstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
    }
	void TextureManager::RenderFrame(std::string id, float x, float y, float width, float height, int row, int frame, float scale, SDL_RendererFlip flip)
	{
		// Set rendering space and render to screen
		SDL_Rect srcRect = 
        { 
            width  * frame,
            height * row, 
            width, 
            height 
        };
		SDL_FRect dstRect = { x, y, width * scale, height * scale };

		// Render to screen
		SDL_RenderCopyExF(Engine::Getinstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
	}

    void TextureManager::RenderText(const std::string& text, int x, int y, TTF_Font* font, SDL_Color color, const int& textScale,unsigned int number)
	{
        std::string finalText = text;
        if (number != UINT_MAX)
        {
            finalText += " " + std::to_string(number);
        }
        
        SDL_Renderer* renderer = mEngine::Engine::Getinstance()->GetRenderer();
		SDL_Surface* surface = CreateTextSurface(finalText, font, color);
		SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

		SDL_Rect rect = { x, y, surface->w * textScale, surface->h * textScale};

        SDL_RenderCopy(renderer, TextTexture, nullptr, &rect);
        SDL_DestroyTexture(TextTexture);
	}

    void TextureManager::SetColor(std::string id, Uint8 red, Uint8 green, Uint8 blue)
    {
        //Modulate texture rgb
        SDL_SetTextureColorMod(m_TextureMap[id], red, green, blue);
    }

    void TextureManager::SetBlendMode(std::string id, SDL_BlendMode blending)
    {
        //Set blending function
        SDL_SetTextureBlendMode(m_TextureMap[id], blending);
    }

    void TextureManager::SetAlpha(std::string id, Uint8 alpha)
    {
        //Modulate texture alpha
        SDL_SetTextureAlphaMod(m_TextureMap[id], alpha);
    }

}