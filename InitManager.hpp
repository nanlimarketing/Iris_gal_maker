//Written by nashdal13
//系统类，用于封装系统函数，让main函数看起来不会那么长（过时）
//初始化类，负责从脚本中读入初始化信息
//First Draft: 2012.3.25
//2012.3.26 revised: 系统类将只读入和存储系统初始化信息
//2012.4.3 Revised: 增加存储鼠标图片
//2012.4.3 Revised: 重命名为初始化类，负责从脚本中读入初始化信息
//2012.4.4 Revised: 增加一系列记录数据

#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif

class InitManager
{
public:
	InitManager(const string filePath); //初始化

	unsigned int height; //记录窗体高度
	unsigned int width; //记录窗体长度
	unsigned int bpp; //记录窗体色深

	unsigned int logoTime; //记录Logo显示的时间
	unsigned int logoAlphaTime; //Logo淡入和淡出的时间

	string windowName; //记录窗体标题
	string windowFlag; //记录窗体信息
	string iconName; //记录图标图片位置
	string mousePicName; //记录鼠标图片位置
	string logoPicName; //记录LOGO图片位置
	sf::Color color; //记录LOGO的背景色
	string resourceFileName; //记录所有的游戏资源的脚本文件名，SystemManager用

	vector<string> fontNames;//字体名称向量
};
