//Written by nashdal13
//背景图片类
//First Draft: 2012.4.4
//2012.4.12 Revised：上次没空写了
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif
#ifndef ANIMEM
	#define ANIMEM
	#include "AnimeManager.hpp"
#endif

class BgManager
{
public:
	BgManager(); //构造函数
	string GetBackground(); //返回
	void SetBackground(const string name); //设置背景
	void DrawBackground(AnimeManager& animeManager,sf::RenderWindow& window); //显示背景
	bool bTransit;
private:
	string bgName; //目前背景所使用的名字
};