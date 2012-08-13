//Written by nashdal13
//主脚本类，执行游戏的脚本
#include "ScriptManager.hpp"
#define WIN

ScriptManager::ScriptManager(InitManager& ini, BgManager& bg, DialogueManager& dm, CharacterManager& cm,AnimeManager& am,sf::Music& b,sf::Music& d,SoundManager& sm,ButtonManager& bm,ObjectsManager& obm):
		initManager(ini),bgManager(bg),dialogueManager(dm),characterManager(cm),animeManager(am),bgm(b),dub(d),soundManager(sm),buttonManager(bm),objectsManager(obm)
{
	state = SRun;
	bAuto = false;
	bInitialized = false;
	bBgm = true;
}

ScriptManager::~ScriptManager()
{
	coms.clear();
}

void ScriptManager::Init(const string scriptName)
{
	wstringstream ss;
	//从脚本文件中读入，采用宽字节
	wifstream infile(scriptName);
	//设置Locale，保证中文读入
	//Windows
#ifdef WIN
	infile.imbue(locale(".936"));
#endif
	//Linux
#ifdef LINUX
	infile.imbue(locale("zh_CN.gbk"));
#endif
	//MAC
#ifdef MAC
	infile.imbue(locale("zh_CN.GBK"));
#endif
	if(!infile)
	{
		//如果找不到文件则显示错误
		throw runtime_error("Cannot open the script file: " + scriptName);
	}
	//临时存储命令
	wstring tempCom;
	while(!infile.eof())
	{
		//读入命令
		getline(infile,tempCom);
		size_t firstSpace = tempCom.find_first_of(L" ",0);
		ss.clear();
		ss.str(L"");
		ss<<tempCom;
		wstring com,vals;
		ss>>com;
		vals.assign(tempCom.begin()+firstSpace+1,tempCom.end());
		//不记录注释
		if(com != L"#")
			coms.push_back(make_pair<wstring,wstring>(com,vals));
	}
	//关闭脚本文件
	infile.close();
	infile.clear();
	//记录所有跳转的位置

	bool bFirst = true;
	vector<pair<wstring,wstring>>::iterator it=coms.begin();
	while(it!=coms.end())
	{	
		//存储第一张背景
		if(bFirst && it->first == L"SetBackground")
		{
			gameFirst = WStringToString(it->second);
			bgName = gameFirst;
			bFirst = false;
		}

		//如果是跳转标记
		if(it->first == L"@")
		{
			if(markIters.count(it->second))
				throw runtime_error("Jump mark duplicated:"+WStringToString(it->second));
			markIters[it->second] = it;	
			coms.erase(it);
		}
		it++;
	}
	//将当前命令迭代器设于开头
	curCom = coms.begin();
}

void ScriptManager::ResetScript()
{
	curCom = coms.begin();
	state = SRun;
	bgName = gameFirst;
}

SState& ScriptManager::State()
{
	return state;
}

bool& ScriptManager::Auto()
{
	return bAuto;
}

void ScriptManager::RunNextScript()
{
	if(curCom!=coms.end())
		curCom++;

}

void ScriptManager::JumpToScript(wstring mark)
{
	curCom = markIters[mark];
	state = SRun;
}

void ScriptManager::JumpToScript(unsigned int num)
{
	curCom += num-1;
	state = SRun;
}

int ScriptManager::GetScriptNum()
{
	return curCom-coms.begin();
}

void ScriptManager::RunScript()
{
	if(curCom != coms.end())
	{
		if(state == SRun)
		{
			wstringstream comStream(curCom->second);
			command = curCom->first;
			if(command == L"Wait")
			{
				state = SWait;
				curCom++;
				clock.Reset();
			}
			else if(command == L"SetBackground")
			{
				//输出背景图像
				//读入背景图像名称
				state = SRun;
				wstring bgName;
				comStream>>bgName;
				//设置背景
				bgManager.SetBackground(WStringToString(bgName));
				clock.Reset();
				curCom++;
			}
			else if(command == L"ChangeBackground")
			{
				state = SRun;
				wstring type,name;
				comStream>>type>>name;
				bgName = WStringToString(name);

				buttonManager.Show() = false;
				characterManager.ShowCharacter() = false;
				dialogueManager.ShowDialogue() = false;

				if(type == L"MoveY")
				{
					objectsManager.AddObject(bgName);
					animeManager.MoveY(bgManager.GetBackground(),0.0f,-static_cast<float>(initManager.height),1.0f);
					animeManager.MoveY(bgName,static_cast<float>(initManager.height),0.0f,1.0f);
					if(animeManager.GetAnime(bgManager.GetBackground()).State() == AFinished)
					{
						animeManager.ResetEffect(bgManager.GetBackground());
						animeManager.GetAnime(bgManager.GetBackground()).SetPositionAll(0.0f,0.0f);
						animeManager.ResetEffect(bgName);
						bgManager.SetBackground(bgName);
						objectsManager.RemoveObject(bgName);

						curCom++;
						clock.Reset();
					}
				}
				if(type == L"MoveX")
				{
					objectsManager.AddObject(bgName);
					animeManager.MoveX(bgManager.GetBackground(),0.0f,static_cast<float>(initManager.width),1.0f);

					animeManager.MoveX(bgName,-static_cast<float>(initManager.width),0.0f,1.0f);
					if(animeManager.GetAnime(bgManager.GetBackground()).State() == AFinished)
					{
						animeManager.ResetEffect(bgManager.GetBackground());
						animeManager.GetAnime(bgManager.GetBackground()).SetPositionAll(0.0f,0.0f);
						animeManager.ResetEffect(bgName);
						bgManager.SetBackground(bgName);
						objectsManager.RemoveObject(bgName);
						curCom++;
						clock.Reset();
					}
				}
				else if(type == L"Fade")
				{
					static string prevBgName;
					static bool bIn;
					unsigned int startValue, endValue;				
					//淡出
					if(!bIn)
					{
						startValue = 255;
						endValue = 0;
					}
					else 
					{
						startValue = 0;
						endValue = 255;
					}
					animeManager.Fade(bgManager.GetBackground(),startValue,endValue,1.0f);
					if(animeManager.GetAnime(bgManager.GetBackground()).State() == AFinished)
					{
						if(!bIn)
						{
							//切换至淡入状态
							prevBgName = bgManager.GetBackground();
							animeManager.GetAnime(bgName).SetAlphaAll(0);

							bgManager.SetBackground(bgName);
							animeManager.ResetEffect(bgName);
							bIn = true;
						}
						else
						{
							animeManager.GetAnime(prevBgName).SetAlphaAll(255);
							animeManager.ResetEffect(prevBgName);
							animeManager.ResetEffect(bgManager.GetBackground());
							bIn = false;

							curCom++;
							clock.Reset();
						}
					}
				}
				else if(type == L"FadeSim")
				{
					animeManager.Fade(bgManager.GetBackground(),255,0,1.0f);
					objectsManager.AddObject(bgName);
					animeManager.Fade(bgName,0,255,1.0f);
					if(animeManager.GetAnime(bgManager.GetBackground()).State() == AFinished)
					{
						animeManager.ResetEffect(bgManager.GetBackground());
						animeManager.GetAnime(bgManager.GetBackground()).SetAlphaAll(255);

						animeManager.ResetEffect(bgName);

						bgManager.SetBackground(bgName);
						objectsManager.RemoveObject(bgName);

						curCom++;
						clock.Reset();
					}
				}
			}
			else if(command == L"AddObject")
			{
				//增加动画
			}
			else if(command == L"RemoveObejct")
			{
				//移除动画
			}
			else if(command == L"AnimeFade")
			{
				//某个动画淡入淡出
			}
			else if(command == L"ShowDialogueBox")
			{
				//显示对话框
				state = SRun;
				dialogueManager.clock.Reset();
				dialogueManager.State() = DInit;
				dialogueManager.ShowDialogue() = true;
				dialogueManager.ShowName() = false;
				
				clock.Reset();
				curCom++;
			}
			else if(command == L"HideDialogueBox")
			{
				//隐藏对话框
				state =SRun;
				dialogueManager.clock.Reset();
				dialogueManager.State() = DExit;
				//隐藏按钮
				buttonManager.Show() = false;
				clock.Reset();
				curCom++;
			}
			else if(command == L"SetDialogueText")
			{
				//设置对话文字
				state = SRun;
				if(dialogueManager.State() == DFinished)
					dialogueManager.State() = DRun;
				wstring name,content;
				comStream>>name>>content;
				if(name == L"NONE")
				{
					//如果不是对话
					dialogueManager.ShowName() = false;
				}
				else
				{
					dialogueManager.SetName(name);
					dialogueManager.SetNameLength(name.size());
					dialogueManager.ShowName() = true;
				}
				dialogueManager.SetContent(content);
			
				clock.Reset();
				curCom++;
			}
			else if(command == L"ShowCharacter")
			{
				//显示人物
				state = SRun;
				characterManager.ShowCharacter() = true;
			
				//读入动作名称
				wstring actionName;
				float pX,pY;
				comStream>>actionName>>pX>>pY;

				//刷新动作
				animeManager.RefreshAnime(WStringToString(actionName));
				//增加人物
				characterManager.SetCharacter(WStringToString(actionName),pX,pY);
				//淡入
				characterManager.FadeIn(WStringToString(actionName),animeManager);

				clock.Reset();
				curCom++;
			}
			else if(command == L"ClearCharacters")
			{
				//删除所有人物
				state = SRun;
				characterManager.ClearCharacter();
				characterManager.ShowCharacter() = false;
				
				clock.Reset();
				curCom++;
			}
			else if(command == L"ClearCharacter")
			{
				//删除某个人物
				wstring actionName;
				comStream>>actionName;
				state = SRun;
				characterManager.ClearCharacter(WStringToString(actionName));

				clock.Reset();
				curCom++;
			}
			else if(command == L"HideCharacter")
			{
				//淡出某一个人物
				state = SRun;
				//读入动作名称
				wstring actionName;
				comStream>>actionName;
				//设置人物淡出
				characterManager.FadeOut(WStringToString(actionName),animeManager);

				clock.Reset();
				curCom++;
			}
			else if(command == L"ShowCG")
			{
				//显示CG
				state =SRun;
				wstring cgName;
				comStream>>cgName;
				//设置背景
				bgManager.SetBackground(WStringToString(cgName));
				//关闭对话框
				dialogueManager.ShowDialogue() = false;
				dialogueManager.State() = DExit;
				//关闭按钮
				buttonManager.Show() = false;
				//关闭人物
				characterManager.ClearCharacter();
				characterManager.ShowCharacter() = false;

				clock.Reset();
				curCom++;
			}
			else if(command == L"SetChoice")
			{
				//显示选项
				state = SChoice;
				dialogueManager.State() = DChoice;
				dialogueManager.SetContent(L"");
				size_t noc;
				comStream>>noc;
				wstring choice,jumpMark;
				for(size_t i = 0; i< noc; i++)
				{
					comStream>>choice>>jumpMark;
					dialogueManager.SetChoice(choice,jumpMark,i);
				}
				clock.Reset();
			}
			else if(command == L"PlayBGM")
			{
				//播放背景音乐
				state = SRun;
				comStream>>bgmName;
				if(!bgm.OpenFromFile(WStringToString(bgmName)))
					throw runtime_error("Cannot find the BGM file:"+WStringToString(bgmName));
				if(bInitialized == false)
					bInitialized = true;
				bgm.SetLoop(true);
				if(bBgm)
					bgm.Play();
				curCom++;
				clock.Reset();
			}
			else if(command == L"PlayDub")
			{
				//播放配音
				state = SRun;
				wstring dubName;
				comStream>>dubName;
				if(!dub.OpenFromFile(WStringToString(dubName)))
					throw runtime_error("Cannot find the Dub file:"+WStringToString(dubName));
				dub.Play();
				curCom++;
				clock.Reset();
			}
			else if(command == L"PlaySoundFX")
			{
				//播放音效
				state = SRun;
				wstring soundFXName;
				comStream>>soundFXName;
				soundManager.PlaySound(WStringToString(soundFXName));
				curCom++;
				clock.Reset();
			}
			else if(command == L"IF")
			{
				state = SRun;
				//判断
				wstring var,sign,mark;
				float val;
				//读入变量符号和比较量及跳转标记
				comStream>>var>>sign>>val>>mark;
				//判断变量是否存在
				if(vars.count(var))
				{
					if(sign == L"==")
					{
						if(vars[var] == val)
						{
							curCom = markIters[mark];
						}
						else
							curCom++;
					}
					else if(sign == L"!=")
					{
						if(vars[var] != val)
						{
							curCom = markIters[mark];
						}
						else
							curCom++;
					}
					else if(sign == L">")
					{
						if(vars[var] > val)
						{
							curCom = markIters[mark];
						}
						else
							curCom++;
					}
					else if(sign == L"<")
					{
						if(vars[var] < val)
						{
							curCom = markIters[mark];
						}
						else
							curCom++;						
					}
					else
						throw runtime_error("Cannot identify the sign" + WStringToString(sign));
				}
				else
					throw runtime_error("Variable" + WStringToString(var) + " doesn't exist.");
				clock.Reset();
			}
			else if(command == L"Float")
			{
				state = SRun;
				//增加变量
				wstring var;
				float val;
				comStream>>var>>val;
				if(vars.count(var))
					throw runtime_error("Variable"+ WStringToString(var) + " already exists.");
				else
				{
					vars[var] = val;
				}
				curCom++;
				clock.Reset();
			}
			else if(command == L"ChangeFloatValue")
			{
				state = SRun;
				//更改变量
				wstring var,sign;
				float val;
				comStream>>var>>sign>>val;
				if(vars.count(var))
				{
					if(sign == L"=")
					{
						vars[var] = val;
					}
					else if(sign == L"+=")
					{
						vars[var] += val;
					}
					else if(sign == L"-=")
					{
						vars[var] -= val;						
					}
					else if(sign == L"*=")
					{
						vars[var] *= val;
					}
					else if(sign == L"/=")
					{
						vars[var] /= val;
					}
					else
						throw runtime_error("Cannot identify the sign" + WStringToString(sign));
				}
				else
					throw runtime_error("Variable" + WStringToString(var) + " doesn't exist.");
				curCom++;
				clock.Reset();
			}
			else if(command == L"WaitFor")
			{
				//等待指定时间
				comStream>>time;
				state = SAuto;
			}
			else if(command == L"Jump")
			{
				//跳转到指定标记处
				state = SRun;
				wstring markName;
				comStream>>markName;
				if(markIters.count(markName))
				{
					curCom = markIters[markName];
					clock.Reset();
				}
				else
					throw runtime_error("Cannot find the jump mark:"+WStringToString(markName));
			}
			else
				throw runtime_error("Cannot identify the command"+WStringToString(command));
		}
		else if(state == SAuto)
		{
			if(clock.GetElapsedTime() > time)
			{
				state = SRun;
				clock.Reset();
				curCom++;
			}
		}
		else if(state == SWait)
		{
			if(bAuto)
			{
				curCom--;
				time = 2.0f;
				state = SAuto;
			}
		}
	}
	else 
	{
		state = SStop;
	}
}