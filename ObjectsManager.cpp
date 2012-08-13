#include "ObjectsManager.hpp"

void ObjectsManager::AddObject(string name)
{
	//添加一个动画
	objects.push_back(name);
}

void ObjectsManager::RemoveObject(string name)
{
	//移除一个动画
	for(vector<string>::iterator iter = objects.begin(); iter != objects.end();)
	{
		if(*iter == name)
			iter = objects.erase(iter);
		else
			iter++;
	}
}

void ObjectsManager::ClearObjects()
{
	//移除所有动画
	objects.clear();
}

void ObjectsManager::Draw(AnimeManager& animeManager, sf::RenderWindow& window)
{
	//绘制所有动画
	for(vector<string>::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		animeManager.DrawAnime(*iter,window);
	}
}