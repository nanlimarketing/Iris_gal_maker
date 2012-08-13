#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif

class SoundManager
{
public:
	SoundManager(); //构造函数，其实是空的^_^
	~SoundManager(); //析构函数，清空所有音效

	bool bPlay; //是否播放音效

	void LoadSounds(const vector<string> _names); //从文件名读取一组音效
	void LoadSound(string _name); //从文件名读取单个音效

	void PlaySound(const string name); //播放音效
	void SetVolume(const float vol); //设置音量

	void ClearSounds(); //清空音效

	float volume; //音量
private:
	map<string, sf::SoundBuffer> m_sounds; //音效映射
	sf::Sound sound;
};