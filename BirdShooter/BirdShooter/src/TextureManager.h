#pragma once
#include <string>
#include <map>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>

namespace mEngine
{
    class TextureManager
    {
    public:
        static inline TextureManager* GetInstance()
        {
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
        }

        bool LoadTexture(std::string id, std::string path);
        SDL_Surface* CreateTextSurface(const std::string& text, TTF_Font* font, SDL_Color color);
        
        void CleanTexture(std::string id);
        void Clean();

        void Render(std::string id, float x, float y, float width, float height, float scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void RenderFrame(std::string id, float x, float y, float width, float height, int row, int frame,float scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void RenderText(const std::string& text, int x, int y,TTF_Font* font, SDL_Color color, const int& textScale = 1, unsigned int number = UINT_MAX);
        

        void SetBlendMode(std::string id, SDL_BlendMode blending);
        void SetColor(std::string id, Uint8 red, Uint8 green, Uint8 blue);
        void SetAlpha(std::string id, Uint8 alpha);

        SDL_Texture* GetTexture(const std::string& id) { return m_TextureMap[id]; }
            
    private:
        static TextureManager* s_Instance;
        std::map<std::string, SDL_Texture* > m_TextureMap;

    };
}