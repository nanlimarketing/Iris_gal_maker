//Written by nashdal13
//动画类，用于记录动画信息
#include "Anime.hpp"

Anime::Anime()
{
	animeName = "NONE";
	totalIndex = 0; //记录有几帧
	curIndex = 0; //记录当前是第几帧
	state = AInit;
	bRepeat = false;
	bFadeInitEffect = false;
	bMoveXInitEffect = false;
	bMoveYInitEffect = false;
	bRotateInitEffect = false;
	bScaleXInitEffect = false;
	bScaleYInitEffect = false;
	bFadeOut = false;
}

Anime::Anime(const string name, vector<string> img, ImageManager& imgManager)
{
	animeName = name; //动画名
	if(name != "NONE")
	{
		imgNames = img; //使用图像的名称
		totalIndex = 0;
		curIndex = 0;
		for(vector<string>::const_iterator iter = img.begin(); iter != img.end(); iter++)
		{
			sf::Sprite tempSprite;
			tempSprite.SetImage(imgManager[*iter]); //获得图片
			sprites.push_back(pair<sf::Sprite,float>(tempSprite,0.0f)); //设置图片
			totalIndex++; //增加总数
		}
		state = AInit;
		bRepeat = false;
		bFadeInitEffect = false;
		bMoveXInitEffect = false;
		bMoveYInitEffect = false;
		bRotateInitEffect = false;
		bScaleXInitEffect = false;
		bScaleYInitEffect = false;
		bFadeOut = false;
	}
}

Anime::Anime(const string name, string img, ImageManager& imgManager)
{
	animeName = name; //动画名
	if(name != "NONE")
	{
		imgNames.push_back(img); //图片名
		totalIndex = 0;
		curIndex = 0;
		sf::Sprite tempSprite;
		tempSprite.SetImage(imgManager[img]); //获得图片
		sprites.push_back(pair<sf::Sprite,float>(tempSprite,0.0f)); //设置图片
		totalIndex++; //增加总数
		state = AInit;
		bRepeat = false;
		bFadeInitEffect = false;
		bMoveXInitEffect = false;
		bMoveYInitEffect = false;
		bRotateInitEffect = false;
		bScaleXInitEffect = false;
		bScaleYInitEffect = false;	
		bFadeOut = false;
	}
}

Anime::~Anime()
{
	//析构函数
	sprites.clear();
}

void Anime::SetName(const string name)
{
	animeName = name;
}
	
void Anime::SetImage(const vector<string> img, ImageManager& imgManager)
{
	//从图像管理器中设置动画
	for(vector<string>::const_iterator iter = img.begin(); iter != img.end(); iter++)
	{
		sf::Sprite tempSprite;
		tempSprite.SetImage(imgManager[*iter]); //获得图片
		sprites.push_back(pair<sf::Sprite,float>(tempSprite,0.0f)); //设置图片并默认设置间隔时间为零
		totalIndex++; //增加总数
	}
}

void Anime::SetImage(unsigned int frameIndex, string img, ImageManager& imgManager)
{ 
	//为某一帧设置图像
	if(frameIndex<totalIndex)
	{
		sprites[frameIndex].first.SetImage(imgManager[img]);
	}
	else
		throw runtime_error("Designated frame does not exist.");
}

void Anime::SetInterval(const float interval, const unsigned int frameIndex)
{
	//为某一帧设置间隔
	sprites[frameIndex].second = interval;
}

void Anime::SetIntervalAll(const float interval)
{
	//为所有帧设置间隔
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->second = interval;
	}
}

void Anime::SetPosition(const float posX, const float posY, const unsigned int frameIndex)
{
	//为某一帧设置位置
	sprites[frameIndex].first.SetPosition(posX,posY);	
}

void Anime::SetPositionAll(const float posX, const float posY)
{
	//为所有帧设置位置
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.SetPosition(posX,posY);
	}
}

void Anime::SetPositionXAll(const float posX)
{
	//为所有帧设置位置
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.SetX(posX);
	}
}

void Anime::SetPositionYAll(const float posY)
{
	//为所有帧设置位置
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.SetY(posY);
	}
}

void Anime::SetCenter(const float posX, const float posY, const unsigned int frameIndex)
{
	//为某一帧设置中心
	sprites[frameIndex].first.SetCenter(posX,posY);
}

void Anime::SetCenterAll(const float posX, const float posY)
{
	//为所有帧设置中心
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.SetCenter(posX,posY);
	}
}

void Anime::SetRotation(const float angle, const unsigned int frameIndex)
{
	//为某一帧设置旋转
	sprites[frameIndex].first.SetRotation(angle);
}

void Anime::SetRotationAll(const float angle)
{
	//为所有帧设置旋转
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.SetRotation(angle);
	}
}

void Anime::SetScale(const float scaleX, const float scaleY, const unsigned int frameIndex)
{
	//为某一帧设置缩放
	sprites[frameIndex].first.SetScale(scaleX,scaleY);
}

void Anime::SetScaleAll(const float scaleX, const float scaleY)
{
	//为所有帧设置旋转
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.SetScale(scaleX,scaleY);
	}
}

void Anime::SetScaleXAll(const float scaleX)
{
	//为所有帧设置旋转
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.SetScaleX(scaleX);
	}
}

void Anime::SetScaleYAll(const float scaleY)
{
	//为所有帧设置旋转
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.SetScaleY(scaleY);
	}
}

void Anime::SetMove(const float moveX, const float moveY, const unsigned int frameIndex)
{
	//为某一帧设置位移
	sprites[frameIndex].first.Move(moveX,moveY);
}

void Anime::SetMoveAll(const float moveX, const float moveY)
{
	//为所有帧设置旋转
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.Move(moveX,moveY);
	}
}

void Anime::SetAlpha(const unsigned int alpha, const unsigned int frameIndex)
{
	sprites[frameIndex].first.SetColor(sf::Color(255,255,255,alpha));
}

void Anime::SetAlphaAll(const unsigned int alpha)
{
	//为所有帧设置旋转
	for(vector<pair<sf::Sprite,float>>::iterator iter = sprites.begin(); iter != sprites.end(); iter++)
	{
		iter->first.SetColor(sf::Color(255,255,255,alpha));
	}
}

const unsigned int Anime::GetTotalIndex()
{
	//获得总帧数
	return totalIndex;
}

unsigned int& Anime::CurIndex()
{
	//获得当前的帧数
	return curIndex;
}

const string Anime::GetName()
{
	//获得动画名
	return animeName;
}

const vector<string> Anime::GetImgNames()
{
	return imgNames;
}

const float Anime::GetInterval(unsigned int frameIndex) 
{
	//获得帧间隔
	return sprites[frameIndex].second;
}

const float Anime::GetCurInterval()
{
	//获得当前的帧间隔
	return sprites[curIndex].second;
}
	
sf::Sprite& Anime::GetCurSprite()
{
	//返回当前的精灵
	return sprites[curIndex].first;
}

sf::Sprite& Anime::GetSprite(unsigned int frameIndex)
{
	//返回指定帧
	return sprites[frameIndex].first;
}

sf::Sprite& Anime::operator[](unsigned int frameIndex)
{
	//用下标返回指定帧
	return sprites[frameIndex].first;
}

sf::Clock& Anime::Clock()
{
	return clock; 
}

AnimeState& Anime::State()
{
	return state;
}

void Anime::SetRepeat(bool bRe)
{
	bRepeat = bRe;
}

bool Anime::GetRepeat()
{
	return bRepeat;
}

bool& Anime::FadeInitEffect()
{
	return bFadeInitEffect;
}

bool& Anime::MoveXInitEffect()
{
	return bMoveXInitEffect;
}

bool& Anime::MoveYInitEffect()
{
	return bMoveYInitEffect;
}

bool& Anime::RotateInitEffect()
{
	return bRotateInitEffect;
}

bool& Anime::ScaleXInitEffect()
{
	return bScaleXInitEffect;
}

bool& Anime::ScaleYInitEffect()
{
	return bScaleYInitEffect;
}

bool& Anime::FadeOut()
{
	return bFadeOut;
}