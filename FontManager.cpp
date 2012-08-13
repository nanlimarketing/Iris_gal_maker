//Written by nashdal13
//字体类，用于管理字体资源
#include "FontManager.hpp"

//构造函数
FontManager::FontManager()
{
	//什么都不做
}

void FontManager::Init(vector<string> fontNames)
{
	//载入Unicode CJK字符集
	vector<sf::Uint32> cjk;
	//载入ASCII
	sf::Uint32 	unicode = 0x0020;
	while(unicode <= 0x007F)
		cjk.push_back(unicode++);
	//载入CJK
	unicode = 0x3000;
	while(unicode <= 0x303F)
		cjk.push_back(unicode++);
	unicode = 0x4E00;		
	while(unicode <= 0x9FA5)
		cjk.push_back(unicode++);
	//载入中文标点
	unicode = 0xFF00;
	while(unicode <= 0xFF8D)
		cjk.push_back(unicode++);
	//读入字符集
	sf::Uint32* unicodeCJK = &cjk[0];
	
	for(vector<string>::const_iterator iter = fontNames.begin(); iter != fontNames.end(); iter++)
	{
		//创建字体
		sf::Font font;
		if(!font.LoadFromFile(iter->c_str(),30,unicodeCJK))
			throw runtime_error("Cannot load the font: "+ (*iter));
		fonts[*iter] = font;
	}
}

sf::Font& FontManager::GetFont(const string fontName)
{
	if(fonts.count(fontName))
	{
		return fonts[fontName];
	}
	else
		throw runtime_error("Cannot find font: "+fontName);
}

sf::Font& FontManager::operator[](const string fontName)
{
	if(fonts.count(fontName))
	{
		return fonts[fontName];
	}
	else
		throw runtime_error("Cannot find font: "+fontName);
}
