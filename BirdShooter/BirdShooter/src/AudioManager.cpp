#include "AudioManager.h"
#include <SDL.h>

namespace mEngine
{
	AudioManager* AudioManager::s_Instance = nullptr;

	Mix_Chunk* mEngine::AudioManager::LoadAudio(const std::string& id,const std::string& path)
	{
		// Check if audio is already loaded
		auto it = m_AudioChunks.find(path);
		if (it != m_AudioChunks.end())
		{
			return it->second;
		}

		Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
		if (sound == nullptr)
		{
			std::cout << "Failed to load audio file: " << path << '\n';
		}

		m_AudioChunks.emplace(id, sound);

		return sound;
	}

	void mEngine::AudioManager::PlayAudio(Mix_Chunk* sound)
	{
		Mix_PlayChannel(-1, sound, 0);
	}

	void mEngine::AudioManager::CleanAudio(const std::string& id)
	{
		Mix_FreeChunk(m_AudioChunks[id]);
		m_AudioChunks[id] = nullptr;
		m_AudioChunks.erase(id);
	}

	void mEngine::AudioManager::Clean()
	{
		for (auto& pair : m_AudioChunks)
		{
			Mix_FreeChunk(pair.second);
		}
		m_AudioChunks.clear();
	}

}