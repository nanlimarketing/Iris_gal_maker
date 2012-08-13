//Written by nashdal13
//文字类，用于处理和显示文字
#include "Text.hpp"

Text::Text()
{
	posX = 0;
	posY = 0;
	maxLength = 400;
	state = TInit;
	charNum = 0;
}

Text::Text(const float width)
{
	posX = 0;
	posY = 0;
	maxLength = static_cast<unsigned int>(width);
	state = TInit;
	charNum = 0;
}

Text::Text(const wstring text, const float width, const float x, const float y, const unsigned int maxLen)
{
	texts.clear();
	originText = text;
	posX = x;
	posY = y;
	if(maxLen == 0)
		maxLength = static_cast<unsigned int>(width - x);
	else
		maxLength = maxLen;
	state = TInit;
	charNum = 0;
}

Text::~Text()
{
	texts.clear();
}

void Text::SetText(const wstring text)
{
	//清除已有的分行文字信息
	texts.clear();
	tempText.clear();
	//设定文字
	originText = text;
	//重设状态
	state = TInit;
	charNum = 0;
}

void Text::SetPosition(const float x, const float y)
{
	//设定位置
	posX = x;
	posY = y;
}

void Text::SetColor(const unsigned int r, const unsigned int g, const unsigned int b)
{
	//设置文字颜色
	color.r = r;
	color.g = g;
	color.b = b;
}
	
void Text::SetMaxLength(const unsigned int maxLen)
{
	//设定单行最长长度
	maxLength = maxLen;
}

TState& Text::State()
{
	return state;
}

unsigned int Text::ProcessText(const float size)
{
	texts.clear();
	//将文字分行
	unsigned int numPerLine = static_cast<unsigned int>(maxLength/size); //每行最多有多少字
	unsigned int numOfLine = static_cast<unsigned int>(tempText.size()/numPerLine); //最多有多少行
	for(unsigned int i = 0; i <= numOfLine; i++)
	{
		wstring tempStr(tempText,i*numPerLine,numPerLine);
		texts.push_back(tempStr);
	}
	
	return numOfLine; //返回行数
}

void Text::DrawText(sf::RenderWindow& window, sf::Font& font, float size, unsigned int interval)
{
	//处理文字
	tempText = originText;
	unsigned int numOfLines = ProcessText(size);
	//建立文字显示
	vector<sf::String> strings;
	for(unsigned int i = 0; i <= numOfLines; i++)
	{
		sf::String tempStr;
		tempStr.SetSize(size); //显示的字体大小
		tempStr.SetPosition(posX,posY+(size+interval)*i); //显示的位置
		tempStr.SetFont(font); //显示的字体
		tempStr.SetColor(color); //显示的颜色
		tempStr.SetText(sf::Unicode::Text(texts[i])); //显示的内容
		strings.push_back(tempStr);
	}
	for(vector<sf::String>::const_iterator iter = strings.begin(); iter != strings.end(); iter++)
		window.Draw(*iter);
	state = TFinished;
}

void Text::DrawTextByChar(sf::RenderWindow& window, sf::Font& font, float time, unsigned int numOfChar, float size, unsigned int interval)
{
	//处理文字
	if(state == TInit)
	{
		clock.Reset();
		endIter = originText.begin();
		state = TRun;
	}
	else if(state == TRun)
	{
		if(clock.GetElapsedTime()>time)
		{
			unsigned int i=0;
			for(unsigned int i=0; i<numOfChar; i++)
			{
				if(charNum<=originText.size())
				{
					charNum++;
				}
				else
				{
					state = TFinished;
				}
			}
			tempText.assign(originText.begin(),originText.begin()+charNum);
			clock.Reset();
		}
	}
	unsigned int numOfLines = ProcessText(size);
	//建立文字显示
	vector<sf::String> strings;
	for(unsigned int i = 0; i <= numOfLines; i++)
	{
		sf::String tempStr;
		tempStr.SetSize(size); //显示的字体大小
		tempStr.SetPosition(posX,posY+(size+interval)*i); //显示的位置
		tempStr.SetFont(font); //显示的字体
		tempStr.SetColor(color); //显示的颜色
		tempStr.SetText(sf::Unicode::Text(texts[i])); //显示的内容
		strings.push_back(tempStr);
	}
	for(vector<sf::String>::const_iterator iter = strings.begin(); iter != strings.end(); iter++)
		window.Draw(*iter);
}
