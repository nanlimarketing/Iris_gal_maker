//人物类，负责处理人物的动作
//Written by nashdal13
#include "CharacterManager.hpp"

CharacterManager::CharacterManager()
{
	bShow = false;
	bFinished = false;
}

CharacterManager::~CharacterManager()
{
	actions.clear();
}

void CharacterManager::SetCharacter(const string name,const float x, const float y)
{
	bFinished = false;
	actions[name] = sf::Vector2f(x,y);
}

map<string,sf::Vector2f>& CharacterManager::GetCharacters()
{
	return actions;
}

CState& CharacterManager::State()
{
	return state;
}

void CharacterManager::DrawCharacter(AnimeManager& animeManager, sf::RenderWindow& window)
{
	if(bShow)
	{
		for(map<string,sf::Vector2f>::iterator iter = actions.begin();iter != actions.end();iter++)
		{
			//如果是淡出结束
			if(animeManager.GetAnime(iter->first).State() == AFinished && animeManager.GetAnime(iter->first).FadeOut())
				actions.erase(iter);
		}

		for(map<string,sf::Vector2f>::iterator iter = actions.begin();iter != actions.end();iter++)
		{
			//如果强制结束播放
			if(bFinished)
			{
				animeManager.GetAnime(iter->first).CurIndex() = animeManager.GetAnime(iter->first).GetTotalIndex() - 1;
				animeManager.GetAnime(iter->first).State() = AFinished;
			}
			animeManager.GetAnime(iter->first).SetPositionAll(iter->second.x,iter->second.y);
			animeManager.DrawAnime(iter->first,window);
		}
	}
}

bool& CharacterManager::ShowCharacter()
{
	return bShow;
}

void CharacterManager::ClearCharacter()
{
	actions.clear();
}

void CharacterManager::ClearCharacter(const string name)
{
	actions.erase(name);
}
void CharacterManager::FinishAction()
{
	if(bFinished == false)
		bFinished = true;
}

bool CharacterManager::Finished(AnimeManager& animeManager)
{
	for(map<string, sf::Vector2f>::iterator iter = actions.begin();iter != actions.end();iter++)
	{
		if(animeManager.GetAnime(iter->first).State() != AFinished)
			return false;
	}
	
	 return true;
}

void CharacterManager::FadeIn(const string name,AnimeManager& animeManager)
{
	animeManager.ResetEffect(name);
	animeManager.Fade(name,0,255,0.5f);
}

void CharacterManager::FadeOut(const string name,AnimeManager& animeManager)
{
	animeManager.ResetEffect(name);
	animeManager.Fade(name,255,0,0.5f);
}