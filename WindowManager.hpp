//Written by nashdal13
//窗体类，用于管理窗体
//First Draft: 2012.3.22
//2012.3.25 Revised: 改为只有一个默认构造函数
//2012.3.28 Revised: 不再负责显示帧速
//2012.4.3 Revised: 增加截屏函数，重新负责显示帧速
#define WIN
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif
#ifdef WIN
	#include <Windows.h>
#endif
//#ifndef TEXT
//	#define TEXT
	#include "Text.hpp"
//#endif


class WindowManager
{
public:
	WindowManager(const unsigned int height, const unsigned int width, 
				const unsigned int bpp, const string windowName, const string windowFlag, const string iconName, const string mousePicName);
	sf::RenderWindow& GetWindow(); //访问窗体接口
	sf::Event& GetEvent(); //访问事件接口
	void SaveScreen(); //截屏
	void SaveScreen(string, string); //截屏至指定路径
	void DisplayFrameRate(sf::Font& font,const float x = 0, const float y = 0);//显示帧速
private:
	sf::RenderWindow mainWindow; //窗体
	sf::Event event; //记录事件
};
