//按钮类
//用于选择和跳转
//First Draft: 2012.4.26

#include "Button.hpp"

Button::Button()
{
	bShowCover = false;
	bClicked = false;
}

bool Button::OnButton(const float x, const float y)
{
	if((x>=buttonX) && (x<=(buttonX+buttonWidth)) && (y>=buttonY) && (y<=(buttonY+buttonHeight)))
	{
		bShowCover = true;
		return true;
	}
	else
	{
		bShowCover = false;
		return false;
	}
}
	
bool& Button::Clicked()
{
	return bClicked;
}

bool& Button::Cover()
{
	return bShowCover;
}

void Button::SetPositionX(const float x)
{
	picX = x;
}

void Button::SetPositionY(const float y)
{
	picY = y;
}

float Button::GetPositionX()
{
	return picX;
}

float Button::GetPositionY()
{
	return picY;
}

float Button::GetOriginPosX()
{
	return oriPicX;
}

float Button::GetOriginPosY()
{
	return oriPicY;
}

string Button::GetPicName()
{
	if(bClicked)
		return clickedName;
	else
		return picName;
}

void Button::Init(const string picN, const string coverN, const string coverCN, const string clickedN, const float pX, const float pY, const float cX, const float cY, 
	unsigned int a, const float bX, const float bY,const unsigned int bW, const unsigned int bH)
{
	picName = picN; //按钮图
	coverName = coverN; //遮罩图
	clickedCoverName = coverCN; //按下遮罩
	clickedName = clickedN; //按下
	picX = pX; //按钮图位置
	oriPicX = pX;
	picY = pY;
	oriPicY = pY;
	coverX = cX; //遮罩图位置
	coverY = cY;
	alpha = a; //遮罩透明度
	buttonX = bX; //判定位置
	buttonY = bY;
	buttonHeight = bH;
	buttonWidth = bW;
}

void Button::DrawButton(AnimeManager& animeManager, sf::RenderWindow& window, bool bEffect = false)
{
	//如需要则绘制按钮图案
	if(bShowCover == false)
	{
		if(bClicked == false)
		{
			if(picName != "NONE")
			{
				if(!bEffect)
					animeManager.GetAnime(picName).SetPositionAll(oriPicX,oriPicY);
				animeManager.DrawAnime(picName,window);
			}
		}
		else
		{
			if(clickedName != "NONE")
			{
				if(!bEffect)
					animeManager.GetAnime(clickedName).SetPositionAll(picX,picY);
				animeManager.DrawAnime(clickedName,window);
			}
		}
	}
	//如需要则绘制遮罩
	else
	{
		if(bClicked == false)
		{
			if(coverName != "NONE")
			{
				animeManager.GetAnime(coverName).SetPositionAll(coverX,coverY);
				animeManager.GetAnime(coverName).SetAlphaAll(alpha);
				animeManager.DrawAnime(coverName,window);
			}
		}
		else
		{
			if(clickedCoverName != "NONE")
			{
				animeManager.GetAnime(clickedCoverName).SetPositionAll(coverX,coverY);
				animeManager.GetAnime(clickedCoverName).SetAlphaAll(alpha);
				animeManager.DrawAnime(clickedCoverName,window);
			}
		}
	}
}

void Button::SetInfo(const wstring t)
{
	info = t;
}

wstring Button::GetInfo()
{
	return info;
}