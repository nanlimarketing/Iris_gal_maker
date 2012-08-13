#include "ObjectsManager.hpp"

void ObjectsManager::AddObject(string name)
{
	//���һ������
	objects.push_back(name);
}

void ObjectsManager::RemoveObject(string name)
{
	//�Ƴ�һ������
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
	//�Ƴ����ж���
	objects.clear();
}

void ObjectsManager::Draw(AnimeManager& animeManager, sf::RenderWindow& window)
{
	//�������ж���
	for(vector<string>::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		animeManager.DrawAnime(*iter,window);
	}
}