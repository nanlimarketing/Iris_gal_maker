//Written by nashdal13
//字体类，用于管理字体资源
//First Draft 2012.3.23
//2012.3.25 Revised: 可记录多入多个字体而不仅仅是一个
//2012.3.27 Revised: 把以前的map的冗余结构改简单了
//2012.4.4 Revised: 将构造函数和初始化分开
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif

class FontManager
{
public:
	FontManager();
	void Init(const vector<string> fontNames);
	sf::Font& GetFont(const string fontName);
	sf::Font& operator[](const string fontName);
private:
	map<string, sf::Font> fonts;
};
