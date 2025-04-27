#include "AudioClip.h"

dae::AudioClip::AudioClip(const std::string& filePath)
{
	//m_chunk = nullptr ?
	m_chunk = Mix_LoadWAV(filePath.c_str());
	if (!m_chunk)
	{
		//throw std::runtime_error("Failed to load sound: " + filePath + "Error: " + Mix_GetError());
	}
}

dae::AudioClip::~AudioClip()
{
	if (m_chunk)
	{
		Mix_FreeChunk(m_chunk);
	}
}

void dae::AudioClip::play() const
{
	Mix_VolumeChunk(m_chunk, static_cast<int>(m_volume * MIX_MAX_VOLUME));
	Mix_PlayChannel(-1, m_chunk, 0);
}


void dae::AudioClip::set_volume(float volume)
{
	m_volume = volume;
}

void dae::AudioClip::load()
{
	//Load into event queue
}

bool dae::AudioClip::is_loaded() const
{
	return m_chunk != nullptr;
}