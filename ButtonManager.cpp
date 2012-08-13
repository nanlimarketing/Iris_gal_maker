#include "ButtonManager.hpp"

ButtonManager::ButtonManager()
{
	curScene = "Main";
	bShow = true;
}

bool& ButtonManager::Show()
{
	return bShow;
}

void ButtonManager::AddButton(const wstring scene, const wstring info, const string picN, const string coverN, const string coverCN, const string clickedN, const float pX, const float pY, const float cX, const float cY, 
	unsigned int a, const float bX, const float bY,const unsigned int bW, const unsigned int bH)
{
	Button button;
	button.Init(picN,coverN,coverCN,clickedN,pX,pY,cX,cY,a,bX,bY,bW,bH);
	button.SetInfo(info);
	if(scene == L"Main")
	{
		if(mainButtons.count(button.GetInfo()) == 0)
			mainButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Setting")
	{
		if(settingButtons.count(button.GetInfo()) == 0)
			settingButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Game")
	{
		if(gameButtons.count(button.GetInfo()) == 0)
			gameButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Sounds")
	{
		if(soundsButtons.count(button.GetInfo()) == 0)
			soundsButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Dialogue")
	{
		if(dialogueButtons.count(button.GetInfo()) == 0)
			dialogueButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Text")
	{
		if(textButtons.count(button.GetInfo()) == 0)
			textButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Exit")
	{
		if(exitButtons.count(button.GetInfo()) == 0)
			exitButtons[button.GetInfo()] = button;
	}
	else if(scene == L"SaveLoad")
	{
		if(slButtons.count(button.GetInfo()) == 0)
			slButtons[button.GetInfo()] = button;
	}
	else
		throw runtime_error("Scene "+WStringToString(scene)+" is not defined");
}

void ButtonManager::AddButton(const wstring scene, Button button)
{
	if(scene == L"Main")
	{
		if(mainButtons.count(button.GetInfo()) == 0)
			mainButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Setting")
	{
		if(settingButtons.count(button.GetInfo()) == 0)
			settingButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Game")
	{
		if(gameButtons.count(button.GetInfo()) == 0)
			gameButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Sounds")
	{
		if(soundsButtons.count(button.GetInfo()) == 0)
			soundsButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Dialogue")
	{
		if(dialogueButtons.count(button.GetInfo()) == 0)
			dialogueButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Text")
	{
		if(textButtons.count(button.GetInfo()) == 0)
			textButtons[button.GetInfo()] = button;
	}
	else if(scene == L"Exit")
	{
		if(exitButtons.count(button.GetInfo()) == 0)
			exitButtons[button.GetInfo()] = button;
	}
	else if(scene == L"SaveLoad")
	{
		if(slButtons.count(button.GetInfo()) == 0)
			slButtons[button.GetInfo()] = button;
	}
	else
		throw runtime_error("Scene "+WStringToString(scene)+" is not defined");
}

Button& ButtonManager::GetButton(const wstring scene, const wstring name)
{
	if(scene == L"Main")
	{
		if(mainButtons.count(name))
			return mainButtons[name];
		else
			throw runtime_error("Cannot find the button "+ WStringToString(name));
	}
	else if(scene == L"Setting")
	{
		if(settingButtons.count(name))
			return settingButtons[name];
		else
			throw runtime_error("Cannot find the button "+WStringToString(name));
	}
	else if(scene == L"Game")
	{
		if(gameButtons.count(name))
			return gameButtons[name];
		else
			throw runtime_error("Cannot find the button "+WStringToString(name));
	}
	else if(scene == L"Sounds")
	{
		if(soundsButtons.count(name))
			return soundsButtons[name];
		else
			throw runtime_error("Cannot find the button "+WStringToString(name));
	}
	else if(scene == L"Dialogue")
	{
		if(dialogueButtons.count(name))
			return dialogueButtons[name];
		else
			throw runtime_error("Cannot find the button "+WStringToString(name));
	}
	else if(scene == L"Text")
	{
		if(textButtons.count(name))
			return textButtons[name];
		else
			throw runtime_error("Cannot find the button "+WStringToString(name));
	}
	else if(scene == L"Exit")
	{
		if(exitButtons.count(name))
			return exitButtons[name];
		else
			throw runtime_error("Cannot find the button "+WStringToString(name));
	}
	else if(scene == L"SaveLoad")
	{
		if(exitButtons.count(name))
			return exitButtons[name];
		else
			throw runtime_error("Cannot find the button "+WStringToString(name));
	}
	else
		throw runtime_error("Scene "+WStringToString(scene)+" is not defined");
}

map<wstring,Button>& ButtonManager::GetButtons(const wstring scene)
{
	if(scene == L"Main")
	{
		return mainButtons;
	}
	else if(scene == L"Game")
	{
		return gameButtons;
	}
	else if(scene == L"Setting")
	{
		return settingButtons;
	}
	else if(scene == L"Sounds")
	{
		return soundsButtons;
	}
	else if(scene == L"Dialogue")
	{
		return dialogueButtons;
	}
	else if(scene == L"Text")
	{
		return textButtons;
	}
	else if(scene == L"Exit")
	{
		return exitButtons;
	}
	else if(scene == L"SaveLoad")
	{
		return slButtons;
	}
	else
		throw runtime_error("Scene "+WStringToString(scene)+" is not defined");
}

void ButtonManager::SetScene(const string scene)
{
	curScene = scene;
}

string ButtonManager::GetScene()
{
	return curScene;
}

wstring ButtonManager::UpdateButtons(const float x, const float y)
{
	wstring returnValue = L"";
	if(curScene == "Main")
	{
		for(map<wstring,Button>::iterator iter = mainButtons.begin(); iter != mainButtons.end(); iter++)
		{
			if(iter->second.OnButton(x,y))
			{
				returnValue = iter->second.GetInfo();
			}
		}
	}
	else if(curScene == "Game")
	{
		if(bShow)
		{
			for(map<wstring,Button>::iterator iter = gameButtons.begin(); iter != gameButtons.end(); iter++)
			{
				if(iter->second.OnButton(x,y))
					returnValue = iter->second.GetInfo();
			}
		}
	}
	else if(curScene == "Exit")
	{
		for(map<wstring,Button>::iterator iter = exitButtons.begin(); iter != exitButtons.end(); iter++)
		{
			if(iter->second.OnButton(x,y))
				returnValue = iter->second.GetInfo();
		}
	}
	else if(curScene == "SaveLoad")
	{
		for(map<wstring,Button>::iterator iter = slButtons.begin(); iter != slButtons.end(); iter++)
		{
			if(iter->second.OnButton(x,y))
				returnValue = iter->second.GetInfo();
		}
	}
	else if(curScene == "Sounds")
	{
		for(map<wstring,Button>::iterator iter = settingButtons.begin(); iter != settingButtons.end(); iter++)
		{
			if(iter->second.OnButton(x,y))
				returnValue = iter->second.GetInfo();
		}
		for(map<wstring,Button>::iterator iter = soundsButtons.begin(); iter != soundsButtons.end(); iter++)
		{
			if(iter->second.OnButton(x,y))
				returnValue = iter->second.GetInfo();
		}
	}
	else if(curScene == "Dialogue")
	{
		for(map<wstring,Button>::iterator iter = settingButtons.begin(); iter != settingButtons.end(); iter++)
		{
			if(iter->second.OnButton(x,y))
				returnValue = iter->second.GetInfo();
		}
		for(map<wstring,Button>::iterator iter = dialogueButtons.begin(); iter != dialogueButtons.end(); iter++)
		{
			if(iter->second.OnButton(x,y))
				returnValue = iter->second.GetInfo();
		}
	}
	else if(curScene == "Text")
	{
		for(map<wstring,Button>::iterator iter = settingButtons.begin(); iter != settingButtons.end(); iter++)
		{
			if(iter->second.OnButton(x,y))
				returnValue = iter->second.GetInfo();
		}
		for(map<wstring,Button>::iterator iter = textButtons.begin(); iter != textButtons.end(); iter++)
		{
			if(iter->second.OnButton(x,y))
				returnValue = iter->second.GetInfo();
		}
	}
	return returnValue;
}

void ButtonManager::DrawButtons(AnimeManager& animeManager, sf::RenderWindow& window, bool bEffect)
{
	if(curScene == "Main")
	{
		if(bShow)
		{
			for(map<wstring,Button>::iterator iter = mainButtons.begin(); iter != mainButtons.end(); iter++)
			{
				iter->second.DrawButton(animeManager,window,bEffect);
			}
		}
	}
	else if(curScene == "Game")
	{
		if(bShow)
		{
			for(map<wstring,Button>::iterator iter = gameButtons.begin(); iter != gameButtons.end(); iter++)
			{
				iter->second.DrawButton(animeManager,window,bEffect);
			}
		}
	}
	else if(curScene == "Sounds")
	{
		for(map<wstring,Button>::iterator iter = settingButtons.begin(); iter != settingButtons.end(); iter++)
		{
			iter->second.DrawButton(animeManager,window,bEffect);
		}
		for(map<wstring,Button>::iterator iter = soundsButtons.begin(); iter != soundsButtons.end(); iter++)
		{
			iter->second.DrawButton(animeManager,window,bEffect);
		}
	}
	else if(curScene == "Dialogue")
	{
		for(map<wstring,Button>::iterator iter = settingButtons.begin(); iter != settingButtons.end(); iter++)
		{
			iter->second.DrawButton(animeManager,window,bEffect);
		}
		for(map<wstring,Button>::iterator iter = dialogueButtons.begin(); iter != dialogueButtons.end(); iter++)
		{
			iter->second.DrawButton(animeManager,window,bEffect);
		}
	}
	else if(curScene == "Text")
	{
		for(map<wstring,Button>::iterator iter = settingButtons.begin(); iter != settingButtons.end(); iter++)
		{
			iter->second.DrawButton(animeManager,window,bEffect);
		}
		for(map<wstring,Button>::iterator iter = textButtons.begin(); iter != textButtons.end(); iter++)
		{
			iter->second.DrawButton(animeManager,window,bEffect);
		}
	}
	else if(curScene == "Exit")
	{
		for(map<wstring,Button>::iterator iter = exitButtons.begin(); iter != exitButtons.end(); iter++)
		{
			iter->second.DrawButton(animeManager,window,bEffect);
		}
	}
	else if(curScene == "SaveLoad")
	{
		for(map<wstring,Button>::iterator iter = slButtons.begin(); iter != slButtons.end(); iter++)
		{
			iter->second.DrawButton(animeManager,window,bEffect);
		}
	}
}