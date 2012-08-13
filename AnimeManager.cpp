//Written by nashdal13
//精灵类，记录精灵的信息
#include "AnimeManager.hpp"

AnimeManager::AnimeManager()
{
}

AnimeManager::~AnimeManager()
{
	animes.clear();
}

void AnimeManager::Fade(const string name, const unsigned int startValue, const unsigned int endValue, const float time)
{
	if(animes[name].FadeInitEffect() == false)
	{
		animes[name].State() = AInit;
		animes[name].SetAlphaAll(startValue);
		Effect effect;
		effect.type = fade;
		effect.startValue = static_cast<float>(startValue);
		effect.endValue = static_cast<float>(endValue);
		effect.step = (effect.endValue-effect.startValue)/time;
		effect.time = time;
		multimap<string,Effect>::iterator iter = effects.insert(make_pair(name,effect));
		iter->second.clock.Reset();
		animes[name].FadeInitEffect() = true;
		if(endValue == 0)
			animes[name].FadeOut() = true;
	}
}

void AnimeManager::MoveX(const string name, const float startValue, const float endValue, const float time)
{
	if(animes[name].MoveXInitEffect() == false)
	{
		animes[name].State() = AInit;
		animes[name].SetPositionXAll(startValue);
		Effect effect;
		effect.type = moveX;
		effect.startValue = static_cast<float>(startValue);
		effect.endValue = static_cast<float>(endValue);
		effect.step = (endValue-startValue)/time;
		effect.time = time;
		multimap<string,Effect>::iterator iter = effects.insert(make_pair(name,effect));
		iter->second.clock.Reset();
		animes[name].MoveXInitEffect() = true;
	}
}

void AnimeManager::MoveY(const string name, const float startValue, const float endValue, const float time)
{
	if(animes[name].MoveYInitEffect() == false)
	{
		animes[name].State() = AInit;
		animes[name].SetPositionYAll(startValue);
		Effect effect;
		effect.type = moveY;
		effect.startValue = static_cast<float>(startValue);
		effect.endValue = static_cast<float>(endValue);
		effect.step = (endValue-startValue)/time;
		effect.time = time;
		multimap<string,Effect>::iterator iter = effects.insert(make_pair(name,effect));
		iter->second.clock.Reset();
		animes[name].MoveYInitEffect() = true;
	}
}

void AnimeManager::Rotate(const string name, const float startValue, const float endValue, const float time)
{
	if(animes[name].RotateInitEffect() == false)
	{
		animes[name].State() = AInit;
		animes[name].SetRotationAll(startValue);
		Effect effect;
		effect.type = rotate;
		effect.startValue = static_cast<float>(startValue);
		effect.endValue = static_cast<float>(endValue);
		effect.step = (endValue-startValue)/time;
		effect.time = time;
		multimap<string,Effect>::iterator iter = effects.insert(make_pair(name,effect));
		iter->second.clock.Reset();
		animes[name].RotateInitEffect() = true;
	}
}

void AnimeManager::ScaleX(const string name, const float startValue, const float endValue, const float time)
{
	if(animes[name].ScaleXInitEffect() == false)
	{
		animes[name].State() = AInit;
		animes[name].SetScaleXAll(startValue);
		Effect effect;
		effect.type = scaleX;
		effect.startValue = static_cast<float>(startValue);
		effect.endValue = static_cast<float>(endValue);
		effect.step = (endValue-startValue)/time;
		effect.time = time;
		multimap<string,Effect>::iterator iter = effects.insert(make_pair(name,effect));
		iter->second.clock.Reset();
		animes[name].ScaleXInitEffect() = true;
	}
}

void AnimeManager::ScaleY(const string name, const float startValue, const float endValue, const float time)
{
	if(animes[name].ScaleYInitEffect() == false)
	{
		animes[name].State() = AInit;
		animes[name].SetScaleYAll(startValue);
		Effect effect;
		effect.type = scaleY;
		effect.startValue = static_cast<float>(startValue);
		effect.endValue = static_cast<float>(endValue);
		effect.step = (endValue-startValue)/time;
		effect.time = time;
		multimap<string,Effect>::iterator iter = effects.insert(make_pair(name,effect));
		iter->second.clock.Reset();
		animes[name].ScaleYInitEffect() = true;
	}
}

void AnimeManager::PushAnime(Anime anime)
{
	if(anime.GetName() != "NONE")
		animes[anime.GetName()] = anime;
}

void AnimeManager::AddAnime(const string name, const string img, ImageManager& imgManager)
{
	imgManager.LoadImage(img);
	Anime tempAnime(name,img,imgManager);
	PushAnime(tempAnime);
}

void AnimeManager::RefreshAnime(const string name)
{
	if(animes.count(name))
	{
		animes[name].CurIndex() = 0;
		animes[name].State() = AInit;
		
	}
	else
		throw runtime_error("AnimeManager cannot find anime: "+name);
}

void AnimeManager::ResetEffect(const string name)
{
	if(animes.count(name))
	{

		animes[name].FadeInitEffect() = false;
		animes[name].MoveXInitEffect() = false;
		animes[name].MoveYInitEffect() = false;
		animes[name].RotateInitEffect() = false;
		animes[name].ScaleXInitEffect() = false;
		animes[name].ScaleYInitEffect() = false;
		animes[name].FadeOut() = false;
	}
	else
		throw runtime_error("AnimeManager cannot find anime: "+name);

}

Anime& AnimeManager::GetAnime(const string name)
{ 
	//返回某个动画
	if(animes.count(name))
		return animes[name];
	else
		throw runtime_error("AnimeManager cannot find anime: "+name);
}

Anime& AnimeManager::operator[](const string name)
{
	//用下标获得某个动画
	if(animes.count(name))
		return animes[name];
	else
		throw runtime_error("AnimeManager cannot find anime: "+name);
}

void AnimeManager::ClearAnimes()
{
	//清空所有的sprite
	animes.clear();
}

void AnimeManager::ClearAnime(const string name,ImageManager& imgManager)
{
	imgManager.ClearImages(animes[name].GetImgNames());
	animes.erase(name);
}

void AnimeManager::DrawAnime(const string name, sf::RenderWindow& window)
{
	//播放某个动画
	if(animes.count(name))
	{
		bool bFinished = true; //特效是否完成
		window.Draw(animes[name].GetCurSprite());//绘制当前帧
		//如果刚初始化则要重置一下时钟
		if(animes[name].State() == AInit)
		{
			animes[name].Clock().Reset();
			animes[name].State() = ARun;
		}
		else if(animes[name].State() == ARun)
		{
			//所有的特效
			pair<effect_it,effect_it> pos = effects.equal_range(name);
			while(pos.first != pos.second)
			{
				if(pos.first->second.clock.GetElapsedTime()<=pos.first->second.time)
				{
					switch(pos.first->second.type)
					{
					case fade:
						{
							animes[name].SetAlphaAll(static_cast<unsigned int>
								(pos.first->second.startValue+pos.first->second.step*pos.first->second.clock.GetElapsedTime()));
						}break;
					case moveX:
						{
							animes[name].SetPositionXAll(
								(pos.first->second.startValue+pos.first->second.step*pos.first->second.clock.GetElapsedTime()));
						}break;
					case moveY:
						{
							animes[name].SetPositionYAll(
								(pos.first->second.startValue+pos.first->second.step*pos.first->second.clock.GetElapsedTime()));
						}break;
					case rotate:
						{
							animes[name].SetRotationAll(
								(pos.first->second.startValue+pos.first->second.step*pos.first->second.clock.GetElapsedTime()));
						}break;
					case scaleX:
						{
							animes[name].SetScaleXAll(
								(pos.first->second.startValue+pos.first->second.step*pos.first->second.clock.GetElapsedTime()));
						}break;
					case scaleY:
						{
							animes[name].SetScaleYAll(
								(pos.first->second.startValue+pos.first->second.step*pos.first->second.clock.GetElapsedTime()));
						}break;
					}
					pos.first->second.finished = false;
					bFinished = false;
				}
				else
				{
					if(pos.first->second.finished == false)
					{
						switch(pos.first->second.type)
						{
						case fade:
							{
								animes[name].SetAlphaAll(static_cast<unsigned int>(pos.first->second.endValue));
							}break;
						case moveX:
							{
								animes[name].SetPositionXAll((pos.first->second.endValue));
							}break;
						case moveY:
							{
								animes[name].SetPositionYAll((pos.first->second.endValue));
							}break;
						case rotate:
							{
								animes[name].SetRotationAll((pos.first->second.endValue));
							}break;
						case scaleX:
							{
								animes[name].SetScaleXAll((pos.first->second.endValue));
							}break;
						case scaleY:
							{
								animes[name].SetScaleXAll((pos.first->second.endValue));
							}break;
						}
						pos.first->second.finished = true;
					}
				}
				pos.first++;
			}
			//清除完成的特效
			while(pos.first != pos.second)
			{
				if(pos.first->second.clock.GetElapsedTime()>pos.first->second.time)
				{
					effects.erase(pos.first);
				}
				pos.first++;
			}
			//动画帧
			if(animes[name].CurIndex() != (animes[name].GetTotalIndex()-1))
			{
				if(animes[name].Clock().GetElapsedTime() >= animes[name].GetCurInterval())
				{
					//若没到最后一帧，且间隔时间足够，则帧数加一
					animes[name].CurIndex()++;
					//清空计时器
					animes[name].Clock().Reset();
				}
			}
			else
			{
				if(animes[name].GetRepeat())
				{
					//如果需要循环播放，则在间隔时间到后重新成第一帧
					if(animes[name].Clock().GetElapsedTime() >= animes[name].GetCurInterval())
					{
						animes[name].CurIndex() = 0;
						//清空计时器
						animes[name].Clock().Reset();
					}
				}
				else
				{
					if(bFinished)
						animes[name].State() = AFinished;
				}
			}
		}
		else if(animes[name].State() = AFinished)
		{
			animes[name].CurIndex() = animes[name].GetTotalIndex()-1; //最后一帧
		}
	}
	else
		throw runtime_error("AnimeManager cannot draw anime: "+name+", because it does not exist.");
}
