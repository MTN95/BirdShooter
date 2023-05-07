#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <SDL_mixer.h>

namespace mEngine
{
	class AudioManager
	{
	public:
		static AudioManager* GetInstance()
		{
			return s_Instance = (s_Instance != nullptr) ? s_Instance : new AudioManager();
		}

		Mix_Chunk* LoadAudio(const std::string& id,const std::string& path);
		
		void PlayAudio(Mix_Chunk* sound);

		void CleanAudio(const std::string& id);
	
		void Clean();
		
	private:
		AudioManager() {}

		static AudioManager* s_Instance;

		std::unordered_map<std::string, Mix_Chunk*> m_AudioChunks;
	};
}