//Written by nashdal13
//背景图片类
//First Draft: 2012.4.4
#include "BgManager.hpp"

BgManager::BgManager()
{
	bTransit = true;
}

void BgManager::SetBackground(const string name)
{
	//当前背景名
	bgName = name;
}

string BgManager::GetBackground()
{
	return bgName;
}

void BgManager::DrawBackground(AnimeManager& animeManager,sf::RenderWindow& window)
{
	//绘制当前背景
	animeManager.DrawAnime(bgName,window);
}