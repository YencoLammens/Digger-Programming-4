#pragma once
#include <iostream>
#include <SDL_mixer.h>
namespace dae
{
	class AudioClip
	{
	public:
		explicit AudioClip(const std::string& filePath);
		/*~AudioClip();*/

		void play() const;
		void set_volume(float volume);
		void load();
		bool is_loaded() const;
		
	private:
		Mix_Chunk* m_chunk{ nullptr };
		float m_volume{ 0.5f };
	};
}


