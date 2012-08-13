#include "SoundManager.hpp"

SoundManager::SoundManager()
{
	volume = 100.0f;
	bPlay = true;
}

SoundManager::~SoundManager()
{
	ClearSounds();
}

void SoundManager::LoadSounds(const vector<string> _names)
{
	//从文件名中读入音效
	for(vector<string>::const_iterator iter = _names.begin(); iter != _names.end(); iter++)
	{
		sf::SoundBuffer buffer;
		if(!buffer.LoadFromFile(iter->c_str()))
			throw runtime_error("Cannot load the sound: " + *iter);
		m_sounds[*iter] = buffer;
	}
}

void SoundManager::LoadSound(const string _name)
{
	sf::SoundBuffer buffer;
	if(!buffer.LoadFromFile(_name.c_str()))
		throw runtime_error("Cannot load the sound: " + _name);
	m_sounds[_name] = buffer;
}

void SoundManager::ClearSounds()
{
	//清空现有音效
	m_sounds.clear();
}

void SoundManager::PlaySound(const string name)
{
	if(bPlay)
	{
		if(m_sounds.count(name))
		{
			sound.SetBuffer(m_sounds[name]);
			sound.Play();
		}
		else
			throw runtime_error("Cannot find the SFX:"+name);
	}
}

void SoundManager::SetVolume(const float vol)
{
	sound.SetVolume(vol);
}