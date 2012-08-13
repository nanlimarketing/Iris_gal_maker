//Written by nashdal13
//文字类，用于处理和显示文字
//First Draft: 2012.3.27
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif

enum TState{TInit,TRun,TFinished};

class Text
{
public:
	Text();
	Text(const float width);
	Text(const wstring text, const float width, const float x = 0, const float y = 0, const unsigned int maxLen = 0);
	~Text();

	void SetText(const wstring text); //设定文字
	void SetPosition(const float x, const float y); //设定位置
	void SetColor(const unsigned int r, const unsigned int g, const unsigned int b); //设置文字颜色
	void SetMaxLength(const unsigned int maxLen); //设定单行最长长度
	TState& State(); //返回状态
	
	void DrawText(sf::RenderWindow& window, sf::Font& font, float size = 30, unsigned int interval = 10); //以指定字体和大小显示
	void DrawTextByChar(sf::RenderWindow& window, sf::Font& font, float time, unsigned int numOfChar, float size = 30, unsigned int interval = 10);
private:
	wstring originText;
	wstring tempText;
	vector<wstring> texts;
	unsigned int charNum;
	wstring::iterator endIter;
	float posX;
	float posY;
	sf::Color color;
	sf::Clock clock;
	unsigned int maxLength;
	TState state;

	unsigned int ProcessText(const float size);
};
