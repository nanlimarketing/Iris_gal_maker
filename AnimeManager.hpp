//Written by nashdal13
//动画类，记录动画信息
//OBSELETE: 精灵类，记录精灵的信息
//First Draft: 2012.3.26
//2012.3.27 Revised: 昨天才写了一半……
//2012.3.27 Revised: 决定推导重建，管理动画，精灵为内部的一个类
//2012.4.4 Revised: 增加清除接口
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif
#ifndef ANIME
	#define ANIME
	#include "Anime.hpp"
#endif
#ifndef WINDOW
	#define WINDOW
	#include "WindowManager.hpp"
#endif

enum EffectType{fade,moveX,moveY,scaleX,scaleY,rotate};

class Effect
{
public:
	EffectType type;
	float time;
	float startValue,endValue;
	float step;
	sf::Clock clock;
	bool finished;
};

typedef multimap<string,Effect>::iterator effect_it;

class AnimeManager
{
public:
	AnimeManager(); //构造函数
	~AnimeManager(); //析构函数
	void PushAnime(Anime anime); //将一个动画存入管理器中
	void AddAnime(const string name, const string img, ImageManager& imgManager); //增加动画
	void RefreshAnime(const string name); //重置某个动画
	void ResetEffect(const string name); //重置效果
	Anime& GetAnime(const string name); //返回某个动画
	Anime& operator[](const string name); //用下标获得某个动画
	void ClearAnimes(); //清空所有的sprite
	void ClearAnime(const string name,ImageManager& imgManager); //清空某个动画
	void DrawAnime(const string name, sf::RenderWindow& window); //播放某个动画

	void Fade(const string name, const unsigned int startValue, const unsigned int endValue, const float time);
	void MoveX(const string name, const float startValue, const float endValue, const float time);
	void MoveY(const string name, const float startValue, const float endValue, const float time);
	void Rotate(const string name, const float startValue, const float endValue, const float time);
	void ScaleX(const string name, const float startValue, const float endValue, const float time);
	void ScaleY(const string name, const float startValue, const float endValue, const float time);
private:
	map<string, Anime> animes;
	multimap<string, Effect> effects;
};
