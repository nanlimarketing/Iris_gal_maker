#include "FileManager.hpp"

FileManager::FileManager()
{
	color = sf::Color::White;
}

FileManager::~FileManager()
{
	fileButtons.clear();
}

void FileManager::AddFileButton(const wstring info, const string picN, const string coverN, const string coverCN, const string clickedN, const float pX, const float pY, const float cX, const float cY, 
	unsigned int a, const float bX, const float bY,const unsigned int bW, const unsigned int bH)
{
	Choice button;
	button.Init(picN,coverN,coverCN,clickedN,pX,pY,cX,cY,a,bX,bY,bW,bH);
	button.SetInfo(info);
	fileButtons.push_back(button);
}

void FileManager::SetTextSize(float s)
{
	size = s;
}

void FileManager::SetText(wstring info, float x, float y, wstring text)
{
	for(vector<Choice>::iterator iter = fileButtons.begin(); iter != fileButtons.end(); iter++)
	{
		if(iter->GetInfo() == info)
		{
			iter->SetText(text,iter->GetPositionX()+x,iter->GetPositionY()+y,size);
			break;
		}
	}
}

wstring FileManager::GetFileButtonText(const wstring info)
{
	vector<Choice>::iterator iter;
	for(iter = fileButtons.begin(); iter != fileButtons.end(); iter++)
	{
		if(iter->GetInfo() == info)
		{
			return iter->GetText();
		}
	}
	if(iter == fileButtons.end())
		throw runtime_error("Cannot find the file button:" + WStringToString(info));
	return L"";
}

Choice& FileManager::GetFileButton(const wstring info)
{
	vector<Choice>::iterator iter;
	for(iter = fileButtons.begin(); iter != fileButtons.end(); iter++)
	{
		if(iter->GetInfo() == info)
		{
			return *iter;
		}
	}
	if(iter == fileButtons.end())
		throw runtime_error("Cannot find the file button:" + WStringToString(info));
}

wstring FileManager::UpdateFileButtons(const float x, const float y)
{
	wstring returnValue = L"";
	for(vector<Choice>::iterator iter = fileButtons.begin(); iter != fileButtons.end(); iter++)
	{
		if(iter->OnButton(x,y))
		{
			returnValue = iter->GetInfo();
		}
	}
	return returnValue;
}

void FileManager::DrawFileButtons(AnimeManager& animeManager, sf::Font& font, sf::RenderWindow& window)
{
	for(vector<Choice>::iterator iter = fileButtons.begin(); iter != fileButtons.end(); iter++)
	{
		iter->DrawChoice(animeManager,color,font,window);
	}
}
