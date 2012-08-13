//对话框类
//用于显示对话框处理对话内容
//Written by nashdal13

#include "DialogueManager.hpp"

void Choice::SetText(const wstring t, const float x, const float y, const float s)
{
	text = t;
	textX = x;
	textY = y;
	textSize = s;
}

void Choice::SetText(const wstring t)
{
	text = t;
}

wstring Choice::GetText()
{
	return text;
}


void Choice::DrawChoice(AnimeManager& animeManager, sf::Color color, sf::Font& font,sf::RenderWindow& window)
{
	DrawButton(animeManager,window,false);
	//如需要则绘制文字
	if(text != L"")
	{
		Text tempText;
		tempText.SetText(text);
		tempText.SetColor(color.r,color.g,color.b);
		tempText.SetPosition(textX,textY);
		tempText.DrawText(window,font,textSize);
	}
}

DialogueManager::DialogueManager(ButtonManager& bm):buttonManager(bm)
{
	bShow = false;
	bShowName = false;
	state = DInit;
	text.SetText(L"");
	nameText.SetText(L"");
	textContent = L"";
}

void DialogueManager::Init(const string pic, const string namePic, const string font, const float pX, const float pY,
	const float pNX, const float pNY, const float mX, const float mY, const float tX, 
	const float tY, const unsigned int maxL, const unsigned int nW, const unsigned int nH, const float size, const unsigned int interval, 
	const float st, const float nt, const float ft, const unsigned int charN, const unsigned int cAlpha, const unsigned int NOC)
{
	picName = pic; //对话框背景名称
	namePicName = namePic; //姓名框背景名称
	picX = pX; //对话框位置X
	picY = pY; //对话框位置Y
	textX = tX; //文字位置X
	textY = tY; //文字位置Y
	maxLength = maxL; //文字最大程度
	textSize = size; //文字大小
	textInterval = interval; //文字行间距
	fontName = font; //文字字体
	slowTime = st; //文字间隔显示时间
	normalTime = nt;
	fastTime = ft;
	charNum = charN; //文字间隔显示字数
	markX = mX; //结尾等待标记位置X
	markY = mY; //结尾等待标记位置Y
	picNX = pNX; //姓名框位置X
	picNY = pNY; //姓名框位置Y
	picNWidth = nW; //姓名框长度
	picNHeight = nH; //姓名框高度

	//建立选择
	for(size_t i = 0; i< NOC; i++)
	{
		Choice choice;
		choice.Init("NONE","cover","NONE","NONE",tX,tY+i*(size+interval),tX,tY+i*(size+interval)-size/10,cAlpha,tX,tY+i*(size+interval)-size/10,maxL,static_cast<unsigned int>(size));
		choices.push_back(choice);
	}
}

void DialogueManager::SetTime(const TextSpeed tS)
{
	textSpeed = tS;
}

TextSpeed DialogueManager::GetTime()
{
	return textSpeed;
}

void DialogueManager::SetContent(const wstring content)
{
	//设置对话框内容
	textContent = content;
	text.SetText(content);
}

void DialogueManager::SetNameLength(const unsigned int length)
{
	//设置姓名长度
	nameLength = length;
}

void DialogueManager::SetName(const wstring name)
{
	//设置姓名
	nameContent = name;
}

void DialogueManager::SetColor(const unsigned int r, const unsigned int g, const unsigned int b)
{
	//设置文字颜色
	color.r = r;
	color.g = g;
	color.b = b;
}

void DialogueManager::SetSize(const float size)
{
	//设置文字大小
	textSize = size;
}

void DialogueManager::SetInterval(const unsigned int interval)
{
	//设置文字行间距
	textInterval = interval;
}

void DialogueManager::SetFont(const string font)
{
	//设置字体
	fontName = font;
}

void DialogueManager::SetBackgroundColor(const unsigned int r, const unsigned int g, const unsigned int b,const unsigned int a)
{
	//设置背景色
	diaColor.a = a;
	diaColor.r = r;
	diaColor.g = g;
	diaColor.b = b;
}


sf::Color DialogueManager::GetDialogueColor()
{
	return diaColor;
}

sf::Color DialogueManager::GetTextColor()
{
	return color;
}

wstring DialogueManager::GetContent()
{
	//获取对话内容
	return textContent;
}
wstring DialogueManager::GetName()
{
	return nameContent;
}
unsigned int DialogueManager::GetNameLength()
{
	//获取姓名长度
	return nameLength;
}

vector<Choice>& DialogueManager::GetChoices()
{
	return choices;
}

unsigned int DialogueManager::GetChoiceNum()
{
	return choiceNum;
}

wstring DialogueManager::UpdateChoice(const float x, const float y)
{
	wstring jump = L"";
	for(vector<Choice>::iterator iter = choices.begin(); iter != choices.end(); iter++)
	{
		if(iter->OnButton(x,y))
			jump = iter->GetInfo();
	}
	return jump;
}

void DialogueManager::SetChoice(const wstring content,const wstring jumpMark,const unsigned int n)
{
	choices[n].SetText(content,textX,textY+n*(textSize+textInterval),textSize);
	choices[n].SetInfo(jumpMark);
	choiceNum = n;
}

void DialogueManager::DrawDialogue(AnimeManager& animeManager,FontManager& fontManager, sf::RenderWindow& window)
{
	//如果是进入阶段
	buttonManager.Show() = false;
	if(state == DInit)
	{
		if(bShow)
		{
		animeManager.GetAnime("diaBg").SetPosition(picX,picY);
		animeManager.GetAnime("diaBg").GetCurSprite().SetColor(diaColor);
		animeManager.GetAnime(picName).SetPosition(picX,picY);
		if(clock.GetElapsedTime() > 0.25f)
		{
			animeManager.GetAnime("diaBg").SetScale(1,1);
			animeManager.GetAnime(picName).SetScale(1,1);
			state = DRun;
		}
		else
		{
			animeManager.GetAnime("diaBg").SetScale(1,clock.GetElapsedTime()*4.0f);
			animeManager.GetAnime(picName).SetScale(1,clock.GetElapsedTime()*4.0f);
		}
		animeManager.DrawAnime("diaBg",window);
		animeManager.DrawAnime(picName,window);
		}
	}
	//如果是离开阶段
	else if(state == DExit)
	{
		if(bShow)
		{
			buttonManager.Show() = false;
			animeManager.GetAnime("diaBg").SetPosition(picX,picY);
			animeManager.GetAnime("diaBg").GetCurSprite().SetColor(diaColor);
			animeManager.GetAnime(picName).SetPosition(picX,picY);
			if(clock.GetElapsedTime() > 0.25f)
			{
				bShow = false;
				textContent = L"";
			}
			else
			{
				animeManager.GetAnime("diaBg").SetScale(1,1-clock.GetElapsedTime()*4.0f);
				animeManager.GetAnime(picName).SetScale(1,1-clock.GetElapsedTime()*4.0f);
			}
			animeManager.DrawAnime("diaBg",window);
			animeManager.DrawAnime(picName,window);
		}
	}
	//如果是显示阶段
	else
	{
		if(bShow)
		{
			buttonManager.Show() = true;
			//显示对话框
			animeManager.GetAnime("diaBg").SetPosition(picX,picY);
			animeManager.GetAnime("diaBg").SetScale(1,1);
			animeManager.GetAnime("diaBg").GetCurSprite().SetColor(diaColor);
			animeManager.DrawAnime("diaBg",window);
			animeManager.GetAnime(picName).SetPosition(picX,picY);
			animeManager.GetAnime(picName).SetScale(1,1);
			animeManager.DrawAnime(picName,window);
			//如果是选项阶段
			if(state == DChoice)
			{
				for(size_t i = 0; i<= choiceNum; i++)
					choices[i].DrawChoice(animeManager,color,fontManager.GetFont(fontName),window);
			}
			else 
			{
				//显示人名
				if(bShowName)
				{
					//人名框
					animeManager.GetAnime("nameBg").SetPosition(picNX,picNY);
					animeManager.GetAnime("nameBg").GetCurSprite().SetColor(diaColor);
					animeManager.DrawAnime("nameBg",window);
					animeManager.GetAnime(namePicName).SetPosition(picNX,picNY);
					animeManager.DrawAnime(namePicName,window);
					//人名文字
					nameTX = picNX + picNWidth/2 -textSize/2*nameLength;
					nameTY = picNY + picNHeight/2 - textSize/2-5;
					nameText.SetPosition(nameTX,nameTY);
					nameText.SetText(nameContent);
					nameText.SetColor(color.r,color.g,color.b);
					nameText.DrawText(window,fontManager.GetFont(fontName),textSize);
				}

				if(textContent != L"")
				{
					text.SetPosition(textX,textY);
					text.SetMaxLength(maxLength);
					text.SetColor(color.r,color.g,color.b);
					if(state == DRun)
					{
						switch(textSpeed)
						{
						case slow:
							{
								text.DrawTextByChar(window,fontManager.GetFont(fontName),slowTime,charNum,textSize,textInterval);
							}break;
						case normal:
							{
								text.DrawTextByChar(window,fontManager.GetFont(fontName),normalTime,charNum,textSize,textInterval);
							}break;
						case fast:
							{
								text.DrawTextByChar(window,fontManager.GetFont(fontName),fastTime,charNum,textSize,textInterval);
							}break;
						}
						if(text.State() == TFinished)
						{
							state = DFinished;
						}
					}
					else if(state == DFinished)
					{
						text.DrawText(window,fontManager.GetFont(fontName),textSize,textInterval);
						animeManager.GetAnime("Mark").SetPositionAll(markX,markY);
						animeManager.DrawAnime("Mark",window);
					}
				}
			}

		}
	}
}

bool& DialogueManager::ShowDialogue()
{
	//是否显示对话框
	return bShow;
}

bool& DialogueManager::ShowName()
{
	//是否显示人名
	return bShowName;
}

DState& DialogueManager::State()
{
	return state;
}