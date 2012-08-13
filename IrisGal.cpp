//Written by nashdal13
//主程序
//First Draft: 2012.3.22
//2012.3.23 Revised: 从脚本读入初始化信息
//2012.3.25 Revised: 将主函数封装成为系统类
//2012.3.25 Revised: 增加输入控制
//2012.3.27 Revised: 增加图像输出
//2012.3.28 Revised: 将显示帧速改在了主程序中
//2012.4.4 Revised: 增加了主循环的控制结构

//#define DEBUG
//Include system headers

#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif

//Include project headers
#ifndef INIT
	#define INIT
	#include "InitManager.hpp"
#endif
#ifndef SYSM
	#define SYSM
	#include "SystemManager.hpp"
#endif
#ifndef WINDOW
	#define WINDOW
	#include "WindowManager.hpp"
#endif
#ifndef FONT
	#define FONT
	#include "FontManager.hpp"
#endif
#ifndef TEXT
	#define TEXT
	#include "Text.hpp"
#endif
#ifndef INPUT
	#define INPUT
	#include "InputManager.hpp"
#endif
#ifndef IMAGE
	#define IMAGE
	#include "ImageManager.hpp"
#endif
#ifndef ANIMEM
	#define ANIMEM
	#include "AnimeManager.hpp"
#endif
#ifndef ANIME
	#define ANIME
	#include "Anime.hpp"
#endif
#ifndef SCRIPT
	#define SCRIPT
	#include "ScriptManager.hpp"
#endif
#ifndef BGMANA
	#define BGMANA
	#include "BgManager.hpp"
#endif
#ifndef DIAM
	#define DIAM
	#include "DialogueManager.hpp"
#endif
#ifndef CHAM
	#define CHAM
	#include "CharacterManager.hpp"
#endif
#ifndef CHAM
	#define CHAM
	#include "CharacterManager.hpp"
#endif
#ifndef SOUNDM
	#define SOUNDM
	#include "SoundManager.hpp"
#endif
#ifndef BUTTONM
	#define BUTTONM
	#include "ButtonManager.hpp"
#endif
#ifndef SET
	#define SET
	#include "Setting.hpp"
#endif
#ifndef OBM
	#define OBM
	#include "ObjectsManager.hpp"
#endif
#ifndef FILEM
	#define FILEM
	#include "FileManager.hpp"
#endif

int main(int argc, char** argv)
{
	try
	{
		//从初始化文件读入初始化信息
		InitManager ini("Resources/Game.setting");
		//文字管理器
		FontManager fontManager;
		//初始化字体
		fontManager.Init(ini.fontNames);
		//输入管理器
		InputManager inputManager;
		//图片管理器
		ImageManager imageManager;
		//动画管理器
		AnimeManager animeManager;
		//背景管理器
		BgManager bgManager;
		//按钮管理器
		ButtonManager buttonManager;
		//对话框管理器
		DialogueManager dialogueManager(buttonManager);
		//人物管理器
		CharacterManager characterManager;
		//文件选项管理器
		FileManager fileManager;
		//背景音乐
		sf::Music bgm;
		//配音
		sf::Music dub;
		//音效
		SoundManager soundManager;
		//其余动画
		ObjectsManager objectsManager;

		//脚本管理器
		ScriptManager scriptManager(ini,bgManager,dialogueManager,characterManager,animeManager,bgm,dub,soundManager,buttonManager,objectsManager);

		//设置
		SettingManager setting;

		//初始化系统
		SystemManager systemManager(ini,imageManager,animeManager,fontManager,inputManager,dialogueManager,characterManager,soundManager,buttonManager,fileManager,scriptManager);

		//初始化窗口
		WindowManager window(ini.width,ini.height,ini.bpp,ini.windowName,ini.windowFlag,ini.iconName,ini.mousePicName);
		//初始化LOGO
		systemManager.Logo();
		
		//主循环
		while(window.GetWindow().IsOpened())
		{
			//判断游戏状态
			switch(systemManager.GameState())
			{
			case Init:
				{
					//显示LOGO
					systemManager.DrawLogo(window.GetWindow());
					//同时在另一个线程初始化
					systemManager.Initialize();
					bgManager.SetBackground(systemManager.mainBg);
					buttonManager.Show() = false;
					bgm.SetVolume(systemManager.bgmVolume);
					dub.SetVolume(systemManager.dubVolume);
				}break;
			case Main:
				{
					//获取输入
					inputManager.UpdateInput(window.GetWindow().GetInput());

					//更新按钮信息
					wstring buttonInfo = buttonManager.UpdateButtons(inputManager.GetMouseX(),inputManager.GetMouseY());	
					
					//输入F2则截屏
					if(inputManager.IsF2KeyPressed())
						window.SaveScreen();					

					//清屏
					window.GetWindow().Clear(sf::Color::White);

					//显示背景
					bgManager.SetBackground(systemManager.mainBg);
					bgManager.DrawBackground(animeManager,window.GetWindow());

					//显示按钮
					buttonManager.DrawButtons(animeManager,window.GetWindow(),false);

					//显示物品
					objectsManager.Draw(animeManager,window.GetWindow());

					//如果按下鼠标左键
					if(inputManager.IsMouseLeftPressed())
					{
						if(buttonInfo != L"")
						{
							if(buttonInfo == L"Game")
							{
								systemManager.GameState() = Transit;
								systemManager.preState = Main;
								scriptManager.ResetScript();
								dialogueManager.ShowDialogue() = false;
								characterManager.ShowCharacter() = false;
							}
							else if(buttonInfo == L"Setting")
							{
								buttonManager.SetScene("Sounds");
								systemManager.GameState() = Setting;
								systemManager.preState = Main;
							}
							else if(buttonInfo == L"Load")
							{
								buttonManager.SetScene("SaveLoad");
								systemManager.GameState() = Load;
								systemManager.preState = Main;
							}
							else if(buttonInfo == L"Continue")
							{
								wifstream infile;
								infile.imbue(locale(".936"));
								infile.open("Save/AutoSave.sav");
								unsigned int scriptNum;
								infile>>scriptNum;
								scriptManager.JumpToScript(scriptNum);
								
								wstring bgName; //背景
								infile>>bgName;
								
								scriptManager.bgName = WStringToString(bgName);
								//人物
								unsigned int numOfCharacters;
								infile>>numOfCharacters;
								characterManager.ShowCharacter() = true;
								for(size_t i = 0; i< numOfCharacters; i++)
								{
									//读入动作名称
									wstring actionName;
									float pX,pY;
									infile>>actionName>>pX>>pY;
									//增加人物
									characterManager.SetCharacter(WStringToString(actionName),pX,pY);
								}
								//是否是选项
								bool bChoice;
								infile>>bChoice;
								if(bChoice)
								{
									dialogueManager.ShowDialogue() = true;
									dialogueManager.State() = DChoice;
									dialogueManager.SetContent(L"");
									size_t noc;
									infile>>noc;
									wstring choice,jumpMark;
									for(size_t i = 0; i<= noc; i++)
									{
										infile>>choice>>jumpMark;
										dialogueManager.SetChoice(choice,jumpMark,i);
									}
								}
								else
								{
									dialogueManager.ShowDialogue() = true;
									dialogueManager.State() = DRun;
									wstring name,content;
									infile>>name>>content;
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
								}
								wstring bgmName;
								infile>>bgmName;
								bgm.OpenFromFile(WStringToString(bgmName));
								infile.close();
								infile.clear();

								systemManager.GameState() = Transit;
								systemManager.preState = Main;
							}
						}
					}
					//输入ESC则退出
					if(inputManager.IsEscKeyPressed())
					{
						systemManager.GameState() = Exit;
						systemManager.exitState = Main;
						buttonManager.SetScene("Exit");
					}

					#ifdef DEBUG
					//显示帧速
					window.DisplayFrameRate(fontManager.GetFont(ini.fontNames[0]));
					#endif

					//如果关闭默认鼠标且显示鼠标则显示自定义鼠标
					if(ini.mousePicName != "DEFAULT" && inputManager.ShowMouse())
						inputManager.DrawMouse(animeManager,window.GetWindow());

					//显示光栅化
					window.GetWindow().Display();
				}break;
			case Game:
				{
					//运行主脚本
					scriptManager.RunScript();
					
					//清屏
					window.GetWindow().Clear(sf::Color::White);

					//显示背景
					bgManager.DrawBackground(animeManager,window.GetWindow());

					//显示物品
					objectsManager.Draw(animeManager,window.GetWindow());

					//显示人物
					characterManager.DrawCharacter(animeManager,window.GetWindow());

					//显示对话框
					dialogueManager.DrawDialogue(animeManager,fontManager,window.GetWindow());
					
					//显示按钮
					buttonManager.DrawButtons(animeManager,window.GetWindow(),false);



					//获取输入
					inputManager.UpdateInput(window.GetWindow().GetInput());
					wstring buttonInfo = buttonManager.UpdateButtons(inputManager.GetMouseX(),inputManager.GetMouseY());
					//读取选择信息
					wstring jump;
					if(scriptManager.State() == SChoice)
						jump = dialogueManager.UpdateChoice(inputManager.GetMouseX(),inputManager.GetMouseY());
					
					//输入F2则截屏
					if(inputManager.IsF2KeyPressed())
						window.SaveScreen();
					//如果按下空格键
					if(inputManager.IsSpaceKeyPressed())
					{
						//如果正在显示文本框则停止显示
						if(dialogueManager.ShowDialogue() == true)
						{
							dialogueManager.ShowDialogue() = false;
							buttonManager.Show() = false;
						}
						else
						{
							//如果不在显示则显示
							if(dialogueManager.State() != DInit)
							{
								dialogueManager.ShowDialogue() = true;
								buttonManager.Show() = true;
							}
						}
					}
					//如果按下鼠标左键
					if(inputManager.IsMouseLeftPressed())
					{
						//按钮
						if(buttonInfo != L"")
						{
							if(buttonInfo == L"Auto")
							{
								//自动运行脚本
								if(scriptManager.Auto() == true)
								{
									buttonManager.GetButton(L"Game",L"Auto").Clicked() = false;
									scriptManager.Auto() = false;
								}
								else
								{
									buttonManager.GetButton(L"Game",L"Auto").Clicked() = true;
									scriptManager.Auto() = true;
								}
							}
							else if(buttonInfo == L"Save")
							{
								setting.preContent = dialogueManager.GetContent();
								setting.preName = dialogueManager.GetName();
								setting.preNameLength = dialogueManager.GetNameLength();
								setting.showDialogue = dialogueManager.ShowDialogue();
								setting.showName = dialogueManager.ShowName();
								setting.preState = dialogueManager.State();
								systemManager.GameState() = Save;
								systemManager.preState = Game;
								systemManager.preBg = bgManager.GetBackground();	
								buttonManager.SetScene("SaveLoad");
								systemManager.screenImage = window.GetWindow().Capture();
							}
						}
						//如果正在播放人物动画则结束动画
						//else if(characterManager.Finished(animeManager) == false)
						//{
						//	characterManager.FinishAction();
						//}
						//如果是选择则跳转
						else if(scriptManager.State() == SChoice && jump != L"")
						{
							dialogueManager.State() = DRun;
							scriptManager.JumpToScript(jump);
						}
						//如果正在显示对话框则立刻显示完全
						else if(dialogueManager.ShowDialogue() && dialogueManager.State() == DInit)
						{
							dialogueManager.State() = DRun;
						}
						//如果正在显式文字则让文字立刻显示完全
						else if(dialogueManager.ShowDialogue() && dialogueManager.State() == DRun)
						{
							dialogueManager.State() = DFinished;
						}
						//若脚本停止则继续运行脚本
						else if(scriptManager.State() == SWait)
						{
							if(dub.GetStatus() == sf::Music::Playing)
								dub.Stop();
							scriptManager.State() = SRun;
						}
						//若脚本自动执行则立刻执行下一句脚本
						else if(scriptManager.State() == SAuto)
						{
							if(dub.GetStatus() == sf::Music::Playing)
								dub.Stop();
							scriptManager.State() = SRun;
							scriptManager.RunNextScript();
						}
					}

					//输入鼠标右键则进入设定菜单
					if(inputManager.IsMouseRightPressed())
					{
						setting.preContent = dialogueManager.GetContent();
						setting.preName = dialogueManager.GetName();
						setting.preNameLength = dialogueManager.GetNameLength();
						setting.showDialogue = dialogueManager.ShowDialogue();
						setting.showName = dialogueManager.ShowName();
						setting.preState = dialogueManager.State();
						systemManager.GameState() = Setting;
						systemManager.preState = Game;
						systemManager.preBg = bgManager.GetBackground();
						buttonManager.SetScene("Sounds");
					}


					//自动存储记录
					wofstream outfile;
					outfile.imbue(locale(".936"));
					outfile.open("Save/AutoSave.sav");

					//脚本位置
					SaveVariable(outfile,scriptManager.GetScriptNum());
					//背景
					SaveVariable(outfile,StringToWString(bgManager.GetBackground()));
					//人物
					//数量
					SaveVariable(outfile,characterManager.GetCharacters().size());
					//名称和位置
					for(map<string,sf::Vector2f>::iterator iter = characterManager.GetCharacters().begin(); 
						iter != characterManager.GetCharacters().end();iter++)
					{
						SaveVariable(outfile,StringToWString(iter->first));
						SaveVariable(outfile,iter->second.x);
						SaveVariable(outfile,iter->second.y);
					}
					//对话框
					//如果是选项
					if(dialogueManager.State() == DChoice)
					{
						SaveVariable(outfile,true);
						SaveVariable(outfile,dialogueManager.GetChoiceNum());
						for(size_t i = 0; i <= dialogueManager.GetChoiceNum(); i++)
						{
							SaveVariable(outfile,dialogueManager.GetChoices()[i].GetText());
							SaveVariable(outfile,dialogueManager.GetChoices()[i].GetInfo());
						}
					}
					else
					{
						SaveVariable(outfile,false);
						if(dialogueManager.GetName() != L"")
							SaveVariable(outfile,dialogueManager.GetName());
						else
						{
							wstring none = L"NONE";
							SaveVariable(outfile,none);
						}
						if(dialogueManager.GetContent() != L"")
							SaveVariable(outfile,dialogueManager.GetContent());
						else
						{
							wstring none = L"NONE";
							SaveVariable(outfile,none);
						}
					}
					//背景音乐
					SaveVariable(outfile,scriptManager.bgmName);

					outfile.close();
					outfile.clear();
					
					#ifdef DEBUG
					//显示帧速
					window.DisplayFrameRate(fontManager.GetFont(systemManager.SystemFont()));
					#endif

					//输入ESC则退出
					if(inputManager.IsEscKeyPressed())
					{
						systemManager.GameState() = Exit;
						systemManager.exitState = Game;
						buttonManager.SetScene("Exit");
					}

					//如果关闭默认鼠标且显示鼠标则显示自定义鼠标
					if(ini.mousePicName != "DEFAULT" && inputManager.ShowMouse())
						inputManager.DrawMouse(animeManager,window.GetWindow());

					//光栅化
					window.GetWindow().Display();

					//脚本结束则返回主菜单
					/*if(scriptManager.State() == SStop)
					{
						buttonManager.Show() = false;
						buttonManager.SetScene("Main");
						bgManager.SetBackground(systemManager.mainBg);
						systemManager.GameState() = Transit;
						systemManager.preState = Init;
						bgm.Stop();
					}*/
				}break;
			case Save:
				{
					//输入F2则截屏
					if(inputManager.IsF2KeyPressed())
						window.SaveScreen();

					bgManager.SetBackground(systemManager.saveBg);

					//获取输入
					inputManager.UpdateInput(window.GetWindow().GetInput());

					wstring fileButtonInfo = fileManager.UpdateFileButtons(inputManager.GetMouseX(),inputManager.GetMouseY());
					wstring buttonInfo = buttonManager.UpdateButtons(inputManager.GetMouseX(),inputManager.GetMouseY());

					//清除上一次留下的缩略图
					objectsManager.ClearObjects();

					//输入ESC则退出
					if(inputManager.IsEscKeyPressed())
					{
						systemManager.GameState() = Exit;
						systemManager.exitState = Save;
						buttonManager.SetScene("Exit");
					}
					//显示图片信息
					if(fileButtonInfo != L"")
					{
						//如果鼠标经过某存档
						//如果不为空
						if(fileManager.GetFileButtonText(fileButtonInfo) != L"Empty")
						{
							objectsManager.AddObject(WStringToString(fileButtonInfo));
						}
					}

					//如果按下鼠标左键
					if(inputManager.IsMouseLeftPressed())
					{
						//如果是返回
						if(buttonInfo == L"Back")
						{
							systemManager.GameState() = Game;
							bgManager.SetBackground(systemManager.preBg);
							if(setting.preState == DChoice)
							{
								dialogueManager.SetContent(L"");
								dialogueManager.State() = DChoice;
							}
							else
							{
								dialogueManager.SetContent(setting.preContent);
								dialogueManager.ShowDialogue() = setting.showDialogue;
								dialogueManager.ShowName() = setting.showName;
								dialogueManager.SetName(setting.preName);
								dialogueManager.SetNameLength(setting.preNameLength);
							}
							buttonManager.SetScene("Game");
						}
						//如果是存档
						if(fileButtonInfo != L"")
						{
							//将截图存储
							string filePath = "Save/";
							systemManager.screenImage.SaveToFile(filePath+WStringToString(fileButtonInfo)+".jpg");
							//重新设置缩略图
							if(fileManager.GetFileButtonText(fileButtonInfo) != L"Empty")
							{
								//存档已经存在
								animeManager.GetAnime(WStringToString(fileButtonInfo)).GetCurSprite().SetImage(systemManager.screenImage);
							}
							else
							{
								//不存在则新建
								animeManager.AddAnime(WStringToString(fileButtonInfo),filePath+WStringToString(fileButtonInfo)+".jpg",imageManager);
								animeManager.GetAnime(WStringToString(fileButtonInfo)).SetPositionAll(systemManager.pos_x,systemManager.pos_y);
								animeManager.GetAnime(WStringToString(fileButtonInfo)).SetScaleAll(systemManager.scale,systemManager.scale);
							}

							wofstream outfile;
							outfile.imbue(locale(".936"));
							outfile.open(filePath+WStringToString(fileButtonInfo)+".sav");
							//获取系统时间
							string time = GetTime();
							string date = GetDate();
							//重设按钮上的时间
							fileManager.GetFileButton(fileButtonInfo).SetText(StringToWString(date)+L" "+StringToWString(time));
							//存储时间
							SaveVariable(outfile,StringToWString(date));
							SaveVariable(outfile,StringToWString(time));
							//存储换行符
							outfile<<"\n";

							//脚本位置
							SaveVariable(outfile,scriptManager.GetScriptNum());
							//背景
							SaveVariable(outfile,StringToWString(systemManager.preBg));
							//人物
							//数量
							SaveVariable(outfile,characterManager.GetCharacters().size());
							//名称和位置
							for(map<string,sf::Vector2f>::iterator iter = characterManager.GetCharacters().begin(); 
								iter != characterManager.GetCharacters().end();iter++)
							{
								SaveVariable(outfile,StringToWString(iter->first));
								SaveVariable(outfile,iter->second.x);
								SaveVariable(outfile,iter->second.y);
							}
							//对话框
							//如果是选项
							if(setting.preState == DChoice)
							{
								SaveVariable(outfile,true);
								SaveVariable(outfile,dialogueManager.GetChoiceNum());
								for(size_t i = 0; i <= dialogueManager.GetChoiceNum(); i++)
								{
									SaveVariable(outfile,dialogueManager.GetChoices()[i].GetText());
									SaveVariable(outfile,dialogueManager.GetChoices()[i].GetInfo());
								}
							}
							else
							{
								SaveVariable(outfile,false);
								if(dialogueManager.GetName() != L"")
									SaveVariable(outfile,setting.preName);
								else
								{
									wstring none = L"NONE";
									SaveVariable(outfile,none);
								}
								if(dialogueManager.GetContent() != L"")
									SaveVariable(outfile,setting.preContent);
								else
								{
									wstring none = L"NONE";
									SaveVariable(outfile,none);
								}
							}
							//背景音乐
							SaveVariable(outfile,scriptManager.bgmName);

							outfile.close();
							outfile.clear();
						}
					}

					//清屏
					window.GetWindow().Clear(sf::Color::White);

					//显示背景
					bgManager.DrawBackground(animeManager,window.GetWindow());
					
					//显示按钮
					fileManager.DrawFileButtons(animeManager,fontManager.GetFont(systemManager.SystemFont()),window.GetWindow());
					buttonManager.DrawButtons(animeManager,window.GetWindow(),false);

					//显示截图
					objectsManager.Draw(animeManager,window.GetWindow());

					//如果关闭默认鼠标且显示鼠标则显示自定义鼠标
					if(ini.mousePicName != "DEFAULT" && inputManager.ShowMouse())
						inputManager.DrawMouse(animeManager,window.GetWindow());

					//光栅化
					window.GetWindow().Display();
				}break;
			case Load:
				{
					//输入F2则截屏
					if(inputManager.IsF2KeyPressed())
						window.SaveScreen();

					//清屏
					window.GetWindow().Clear(sf::Color::White);

					//显示背景
					bgManager.DrawBackground(animeManager,window.GetWindow());
					bgManager.SetBackground(systemManager.loadBg);
					
					//显示按钮
					fileManager.DrawFileButtons(animeManager,fontManager.GetFont(systemManager.SystemFont()),window.GetWindow());
					buttonManager.DrawButtons(animeManager,window.GetWindow(),false);

					//显示缩略图
					objectsManager.Draw(animeManager,window.GetWindow());

					//获取输入
					inputManager.UpdateInput(window.GetWindow().GetInput());
					wstring fileButtonInfo = fileManager.UpdateFileButtons(inputManager.GetMouseX(),inputManager.GetMouseY());
					wstring buttonInfo = buttonManager.UpdateButtons(inputManager.GetMouseX(),inputManager.GetMouseY());

					//清除上一次留下的缩略图
					objectsManager.ClearObjects();

					//输入ESC则退出
					if(inputManager.IsEscKeyPressed())
					{
						systemManager.GameState() = Exit;
						systemManager.exitState = Load;
						buttonManager.SetScene("Exit");
					}
					//显示图片信息
					if(fileButtonInfo != L"")
					{
						//如果鼠标经过某存档
						//如果不为空
						if(fileManager.GetFileButtonText(fileButtonInfo) != L"Empty")
						{
							objectsManager.AddObject(WStringToString(fileButtonInfo));
						}
					}
					//如果按下鼠标左键
					if(inputManager.IsMouseLeftPressed())
					{
						//如果是返回
						if(buttonInfo == L"Back")
						{
							if(systemManager.preState == Game)
							{
								systemManager.GameState() = Game;
								bgManager.SetBackground(systemManager.preBg);
								if(setting.preState == DChoice)
								{
									dialogueManager.SetContent(L"");
									dialogueManager.State() = DChoice;
								}
								else
								{
									dialogueManager.SetContent(setting.preContent);
									dialogueManager.ShowDialogue() = setting.showDialogue;
									dialogueManager.ShowName() = setting.showName;
									dialogueManager.SetName(setting.preName);
									dialogueManager.SetNameLength(setting.preNameLength);
								}
								buttonManager.SetScene("Game");
							}
							else if(systemManager.preState == Main)
							{
								systemManager.GameState() = Main;
								buttonManager.SetScene("Main");
							}
						}
						//如果是读档
						if(fileButtonInfo != L"")
						{
							//判断档案是否已经存在
							if(fileManager.GetFileButtonText(fileButtonInfo) != L"Empty")
							{
								//不存在则读档
								string filePath = "Save/";
								wifstream infile;
								infile.imbue(locale(".936"));
								infile.open(filePath+WStringToString(fileButtonInfo)+".sav");

								//跳过时间
								JumpOneVariable(infile);
								JumpOneVariable(infile);

								unsigned int scriptNum;
								infile>>scriptNum;
								scriptManager.JumpToScript(scriptNum);
								wstring bgName; //背景
								infile>>bgName;
								
								scriptManager.bgName = WStringToString(bgName);
								//人物
								unsigned int numOfCharacters;
								infile>>numOfCharacters;
								characterManager.ShowCharacter() = true;
								for(size_t i = 0; i< numOfCharacters; i++)
								{
									//读入动作名称
									wstring actionName;
									float pX,pY;
									infile>>actionName>>pX>>pY;
									//增加人物
									characterManager.SetCharacter(WStringToString(actionName),pX,pY);
								}
								//是否是选项
								bool bChoice;
								infile>>bChoice;
								if(bChoice)
								{
									dialogueManager.ShowDialogue() = true;
									dialogueManager.State() = DChoice;
									dialogueManager.SetContent(L"");
									size_t noc;
									infile>>noc;
									wstring choice,jumpMark;
									for(size_t i = 0; i<= noc; i++)
									{
										infile>>choice>>jumpMark;
										dialogueManager.SetChoice(choice,jumpMark,i);
									}
								}
								else
								{
									dialogueManager.ShowDialogue() = true;
									dialogueManager.State() = DRun;
									wstring name,content;
									infile>>name>>content;
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
								}
								wstring bgmName;
								infile>>bgmName;
								bgm.OpenFromFile(WStringToString(bgmName));
								infile.close();
								infile.clear();
								
								buttonManager.Show() = false;
								objectsManager.ClearObjects();
								systemManager.GameState() = Transit;
								systemManager.preState = Load;
							}							
						}
					}



					//如果关闭默认鼠标且显示鼠标则显示自定义鼠标
					if(ini.mousePicName != "DEFAULT" && inputManager.ShowMouse())
						inputManager.DrawMouse(animeManager,window.GetWindow());

					//光栅化
					window.GetWindow().Display();

				}break;
			case Setting:
				{
					//输入F2则截屏
					if(inputManager.IsF2KeyPressed())
						window.SaveScreen();

					bgManager.SetBackground(systemManager.setBg);
					//获取输入
					inputManager.UpdateInput(window.GetWindow().GetInput());
					wstring buttonInfo = buttonManager.UpdateButtons(inputManager.GetMouseX(),inputManager.GetMouseY());

					//如果一直按着鼠标左键
					if(inputManager.IsMouseLeftDown())
					{
						if(buttonInfo != L"")
						{
							if(buttonInfo == L"BGMVolUp")
							{
								if(systemManager.bgmVolume <= 99.0f)
									systemManager.bgmVolume += 1.0f;
								bgm.SetVolume(systemManager.bgmVolume);
							}
							else if(buttonInfo == L"BGMVolDown")
							{
								if(systemManager.bgmVolume >= 1.0f)
									systemManager.bgmVolume -= 1.0f;
								bgm.SetVolume(systemManager.bgmVolume);
							}
							//配音音量增
							else if(buttonInfo == L"DubVolUp")
							{
								if(systemManager.dubVolume <= 99.0f)
									systemManager.dubVolume += 1.0f;
								dub.SetVolume(systemManager.dubVolume);
							}
							//配音音量减
							else if(buttonInfo == L"DubVolDown")
							{
								if(systemManager.dubVolume >= 1.0f)	
									systemManager.dubVolume -= 1.0f;
								dub.SetVolume(systemManager.dubVolume);
							}
							//音效音量增
							else if(buttonInfo == L"SoundVolUp")
							{
								if(soundManager.volume <= 99.0f)
									soundManager.volume += 1.0f;
								soundManager.SetVolume(soundManager.volume);
							}
							//音效音量减
							else if(buttonInfo == L"SoundVolDown")
							{
								if(soundManager.volume >= 1.0f)
									soundManager.volume -= 1.0f;
								soundManager.SetVolume(soundManager.volume);
							}
							//背景红色增
							else if(buttonInfo == L"DialogueRedUp")
							{
								unsigned int color = dialogueManager.GetDialogueColor().r;
								if(color<=254)
									dialogueManager.SetBackgroundColor(color+1,dialogueManager.GetDialogueColor().g,dialogueManager.GetDialogueColor().b,dialogueManager.GetDialogueColor().a);
							}
							//背景红色减
							else if(buttonInfo == L"DialogueRedDown")
							{
								unsigned int color = dialogueManager.GetDialogueColor().r;
								if(color>=1)
									dialogueManager.SetBackgroundColor(color-1,dialogueManager.GetDialogueColor().g,dialogueManager.GetDialogueColor().b,dialogueManager.GetDialogueColor().a);
							}
							//背景绿色增
							else if(buttonInfo == L"DialogueGreenUp")
							{
								unsigned int color = dialogueManager.GetDialogueColor().g;
								if(color<=254)
									dialogueManager.SetBackgroundColor(dialogueManager.GetDialogueColor().r,color+1,dialogueManager.GetDialogueColor().b,dialogueManager.GetDialogueColor().a);
							}
							//背景绿色减
							else if(buttonInfo == L"DialogueGreenDown")
							{
								unsigned int color = dialogueManager.GetDialogueColor().g;
								if(color>=1)
									dialogueManager.SetBackgroundColor(dialogueManager.GetDialogueColor().r,color-1,dialogueManager.GetDialogueColor().b,dialogueManager.GetDialogueColor().a);
							}
							//背景蓝色增
							else if(buttonInfo == L"DialogueBlueUp")
							{
								unsigned int color = dialogueManager.GetDialogueColor().b;
								if(color<=254)
									dialogueManager.SetBackgroundColor(dialogueManager.GetDialogueColor().r,dialogueManager.GetDialogueColor().g,color+1,dialogueManager.GetDialogueColor().a);
							}
							//背景蓝色减
							else if(buttonInfo == L"DialogueBlueDown")
							{
								unsigned int color = dialogueManager.GetDialogueColor().b;
								if(color>=1)
									dialogueManager.SetBackgroundColor(dialogueManager.GetDialogueColor().a,dialogueManager.GetDialogueColor().g,color-1,dialogueManager.GetDialogueColor().a);
							}
							//背景透明度增
							else if(buttonInfo == L"DialogueAlphaUp")
							{
								unsigned int color = dialogueManager.GetDialogueColor().a;
								if(color<=254)
									dialogueManager.SetBackgroundColor(dialogueManager.GetDialogueColor().r,dialogueManager.GetDialogueColor().g,dialogueManager.GetDialogueColor().b,color+1);
							}
							//背景透明度减
							else if(buttonInfo == L"DialogueAlphaDown")
							{
								unsigned int color = dialogueManager.GetDialogueColor().a;
								if(color>=1)
									dialogueManager.SetBackgroundColor(dialogueManager.GetDialogueColor().r,dialogueManager.GetDialogueColor().g,dialogueManager.GetDialogueColor().b,color-1);
							}
							//文字红色增
							else if(buttonInfo == L"TextRedUp")
							{
								unsigned int color = dialogueManager.GetTextColor().r;
								if(color<=254)
									dialogueManager.SetColor(color+1,dialogueManager.GetTextColor().g,dialogueManager.GetTextColor().b);
							}
							//文字红色减
							else if(buttonInfo == L"TextRedDown")
							{
								unsigned int color = dialogueManager.GetTextColor().r;
								if(color>=1)
									dialogueManager.SetColor(color-1,dialogueManager.GetTextColor().g,dialogueManager.GetTextColor().b);
							}
							//文字绿色增
							else if(buttonInfo == L"TextGreenUp")
							{
								unsigned int color = dialogueManager.GetTextColor().g;
								if(color<=254)
									dialogueManager.SetColor(dialogueManager.GetTextColor().r,color+1,dialogueManager.GetTextColor().b);
							}
							//文字绿色减
							else if(buttonInfo == L"TextGreenDown")
							{
								unsigned int color = dialogueManager.GetTextColor().g;
								if(color>=1)
									dialogueManager.SetColor(dialogueManager.GetTextColor().r,color-1,dialogueManager.GetTextColor().b);
							}
							//背景蓝色增
							else if(buttonInfo == L"TextBlueUp")
							{
								unsigned int color = dialogueManager.GetTextColor().b;
								if(color<=254)
									dialogueManager.SetColor(dialogueManager.GetTextColor().r,dialogueManager.GetTextColor().g,color+1);
							}
							//背景蓝色减
							else if(buttonInfo == L"TextBlueDown")
							{
								unsigned int color = dialogueManager.GetTextColor().b;
								if(color>=1)
									dialogueManager.SetColor(dialogueManager.GetTextColor().r,dialogueManager.GetTextColor().g,color-1);
							}
						}
					}

					//清屏
					window.GetWindow().Clear(sf::Color::White);

					//显示背景
					bgManager.DrawBackground(animeManager,window.GetWindow());
					//绘制设置界面
					if(buttonManager.GetScene() == "Sounds")
					{
						//界面
						animeManager.DrawAnime(systemManager.sounds,window.GetWindow());
						//显示音量
						stringstream sstream;
						//背景音乐
						sstream<<static_cast<int>(systemManager.bgmVolume);
						string bgmVolume;
						sstream>>bgmVolume;
						systemManager.bgmVol.SetText(StringToWString(bgmVolume));
						systemManager.bgmVol.SetColor(255,255,255);
						systemManager.bgmVol.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));
						//音效
						sstream.clear();
						sstream.str("");
						sstream<<static_cast<int>(soundManager.volume);
						string sfxVolume;
						sstream>>sfxVolume;
						systemManager.sfxVol.SetText(StringToWString(sfxVolume));
						systemManager.sfxVol.SetColor(255,255,255);
						systemManager.sfxVol.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));			
						//配音
						sstream.clear();
						sstream.str("");
						sstream<<static_cast<int>(systemManager.dubVolume);
						string dubVolume;
						sstream>>dubVolume;
						systemManager.dubVol.SetText(StringToWString(dubVolume));
						systemManager.dubVol.SetColor(255,255,255);
						systemManager.dubVol.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));
						//按钮
						if(scriptManager.bBgm)
							buttonManager.GetButton(L"Sounds",L"BGM").Clicked() = false;
						else
							buttonManager.GetButton(L"Sounds",L"BGM").Clicked() = true;
						if(scriptManager.bDub)
							buttonManager.GetButton(L"Sounds",L"Dub").Clicked() = false;
						else
							buttonManager.GetButton(L"Sounds",L"Dub").Clicked() = true;
						if(soundManager.bPlay)
							buttonManager.GetButton(L"Sounds",L"Sound").Clicked() = false;
						else
							buttonManager.GetButton(L"Sounds",L"Sound").Clicked() = true;
					}
					else if(buttonManager.GetScene() == "Dialogue")
					{
						//界面
						animeManager.DrawAnime(systemManager.dialogue,window.GetWindow());
						//显示颜色
						stringstream sstream;
						//红色
						sstream<<static_cast<int>(dialogueManager.GetDialogueColor().r);
						string red;
						sstream>>red;
						systemManager.red.SetText(StringToWString(red));
						systemManager.red.SetColor(255,255,255);
						systemManager.red.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));
						//绿色
						sstream.clear();
						sstream.str("");
						sstream<<static_cast<int>(dialogueManager.GetDialogueColor().g);
						string green;
						sstream>>green;
						systemManager.green.SetText(StringToWString(green));
						systemManager.green.SetColor(255,255,255);
						systemManager.green.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));	
						//蓝色
						sstream.clear();
						sstream.str("");
						sstream<<static_cast<int>(dialogueManager.GetDialogueColor().b);
						string blue;
						sstream>>blue;
						systemManager.blue.SetText(StringToWString(blue));
						systemManager.blue.SetColor(255,255,255);
						systemManager.blue.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));	
						//透明度
						sstream.clear();
						sstream.str("");
						sstream<<static_cast<int>(dialogueManager.GetDialogueColor().a);
						string alpha;
						sstream>>alpha;
						systemManager.alpha.SetText(StringToWString(alpha));
						systemManager.alpha.SetColor(255,255,255);
						systemManager.alpha.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));	
						//显示对话框	
						dialogueManager.ShowDialogue() = true;

						if(!setting.bInitialized)
						{
							dialogueManager.State() = DRun;
							dialogueManager.ShowName() = true;
							dialogueManager.SetName(L"系统消息");
							dialogueManager.SetNameLength(4);
							dialogueManager.SetContent(L"这是一段测试性的文字，供您参考颜色和速度信息。");
							setting.bInitialized = true;
						}
						dialogueManager.DrawDialogue(animeManager,fontManager,window.GetWindow());
					}
					else if(buttonManager.GetScene() == "Text")
					{
						//界面
						animeManager.DrawAnime(systemManager.text,window.GetWindow());
						//显示文字颜色
						//显示颜色
						stringstream sstream;
						//红色
						sstream<<static_cast<int>(dialogueManager.GetTextColor().r);
						string red;
						sstream>>red;
						systemManager.tRed.SetText(StringToWString(red));
						systemManager.tRed.SetColor(255,255,255);
						systemManager.tRed.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));
						//绿色
						sstream.clear();
						sstream.str("");
						sstream<<static_cast<int>(dialogueManager.GetTextColor().g);
						string green;
						sstream>>green;
						systemManager.tGreen.SetText(StringToWString(green));
						systemManager.tGreen.SetColor(255,255,255);
						systemManager.tGreen.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));	
						//蓝色
						sstream.clear();
						sstream.str("");
						sstream<<static_cast<int>(dialogueManager.GetTextColor().b);
						string blue;
						sstream>>blue;
						systemManager.tBlue.SetText(StringToWString(blue));
						systemManager.tBlue.SetColor(255,255,255);
						systemManager.tBlue.DrawText(window.GetWindow(),fontManager.GetFont(systemManager.SystemFont()));
						//显示对话框
						dialogueManager.ShowDialogue() = true;

						if(!setting.bInitialized)
						{
							dialogueManager.State() = DRun;
							dialogueManager.ShowName() = true;
							dialogueManager.SetName(L"系统消息");
							dialogueManager.SetNameLength(4);
							dialogueManager.SetContent(L"这是一段测试性的文字，供您参考颜色和速度信息。");
							setting.bInitialized = true;
						}
						dialogueManager.DrawDialogue(animeManager,fontManager,window.GetWindow());
					}

					//显示按钮
					buttonManager.DrawButtons(animeManager,window.GetWindow(),false);

					//输入鼠标右键则返回上一界面
					if(inputManager.IsMouseRightPressed())
					{	
						switch(systemManager.preState)
						{
						case Main:
							{
								buttonManager.SetScene("Main");
							}break;
						case Game:
							{
								bgManager.SetBackground(systemManager.preBg);
								if(setting.preState == DChoice)
								{
									dialogueManager.SetContent(L"");
									dialogueManager.State() = DChoice;
								}
								else
								{
									dialogueManager.SetContent(setting.preContent);
									dialogueManager.ShowDialogue() = setting.showDialogue;
									dialogueManager.ShowName() = setting.showName;
									dialogueManager.SetName(setting.preName);
									dialogueManager.SetNameLength(setting.preNameLength);
								}
								buttonManager.SetScene("Game");
							}break;
						}
						setting.bInitialized = false;
						systemManager.GameState() = systemManager.preState;
					}
					//如果按下鼠标左键
					if(inputManager.IsMouseLeftPressed())
					{
						if(buttonInfo != L"")
						{
							//返回前一界面
							if(buttonInfo == L"Back")
							{
								switch(systemManager.preState)
								{
								case Main:
									{
										buttonManager.SetScene("Main");
									}break;
								case Game:
									{
										bgManager.SetBackground(systemManager.preBg);
									if(setting.preState == DChoice)
									{
										dialogueManager.SetContent(L"");
										dialogueManager.State() = DChoice;
									}
									else
									{
										dialogueManager.SetContent(setting.preContent);
										dialogueManager.ShowDialogue() = setting.showDialogue;
										dialogueManager.ShowName() = setting.showName;
										dialogueManager.SetName(setting.preName);
										dialogueManager.SetNameLength(setting.preNameLength);
									}
										buttonManager.SetScene("Game");
									}break;
								}
								setting.bInitialized = false;
								systemManager.GameState() = systemManager.preState;
							}
							//声音设定
							else if(buttonInfo == L"Sounds")
							{
								setting.bInitialized = false;
								buttonManager.SetScene("Sounds");
							}
							else if(buttonInfo == L"Dialogue")
							{
								setting.bInitialized = false;
								buttonManager.SetScene("Dialogue");
							}
							else if(buttonInfo == L"Text")
							{
								setting.bInitialized = false;
								buttonManager.SetScene("Text");
							}
							//背景音乐开关
							else if(buttonInfo == L"BGM")
							{
								if(!scriptManager.bBgm)
								{
									scriptManager.bBgm = true;
									if(scriptManager.bInitialized)
										bgm.Play();
								}
								else
								{
									scriptManager.bBgm = false;
									bgm.Stop();
								}
							}
							//配音开关
							else if(buttonInfo == L"Dub")
							{
								if(!scriptManager.bDub)
								{
									scriptManager.bDub = true;
								}
								else
								{
									scriptManager.bDub = false;
									dub.Stop();
								}
							}
							//音效开关
							else if(buttonInfo == L"Sound")
							{
								if(soundManager.bPlay)
								{
									soundManager.bPlay = false;
								}
								else
								{
									soundManager.bPlay = true;
								}
							}
							else if(buttonInfo == L"Slow")
							{
								dialogueManager.SetTime(slow);
								setting.bInitialized = false;
							}
							else if(buttonInfo == L"Normal")
							{
								dialogueManager.SetTime(normal);
								setting.bInitialized = false;
							}
							else if(buttonInfo == L"Fast")
							{
								dialogueManager.SetTime(fast);
								setting.bInitialized = false;
							}
						}
					}
					//输入ESC则退出
					if(inputManager.IsEscKeyPressed())
					{
						systemManager.GameState() = Exit;
						systemManager.exitState = Setting;
						buttonManager.SetScene("Exit");
					}

					#ifdef DEBUG
					//显示帧速
					window.DisplayFrameRate(fontManager.GetFont(ini.fontNames[0]));
					#endif

					//如果关闭默认鼠标且显示鼠标则显示自定义鼠标
					if(ini.mousePicName != "DEFAULT" && inputManager.ShowMouse())
						inputManager.DrawMouse(animeManager,window.GetWindow());

					//显示光栅化
					window.GetWindow().Display();

				}break;
			case Transit:
				{
					//如果是进入主菜单
					if(systemManager.preState == Init)
					{
						//淡入菜单
						animeManager.Fade(bgManager.GetBackground(),0,255,1.0f);
						if(animeManager.GetAnime(bgManager.GetBackground()).State() == AFinished)
						{
							bool finished = true;
							//淡入按钮
							for(map<wstring,Button>::iterator iter = buttonManager.GetButtons(L"Main").begin(); iter != buttonManager.GetButtons(L"Main").end(); iter++)
							{
								animeManager.MoveX(iter->second.GetPicName(),iter->second.GetOriginPosX(),iter->second.GetOriginPosX(),1.0f);
								animeManager.MoveY(iter->second.GetPicName(),iter->second.GetOriginPosY()-20,iter->second.GetOriginPosY(),1.0f);
								animeManager.Fade(iter->second.GetPicName(),0,255,1.0f);
								if(animeManager.GetAnime(iter->second.GetPicName()).State() != AFinished)
									finished = false;
							}
							buttonManager.Show() = true;
							if(finished)
							{
								for(map<wstring,Button>::iterator iter = buttonManager.GetButtons(L"Main").begin(); iter != buttonManager.GetButtons(L"Main").end(); iter++)
								{
									animeManager.ResetEffect(iter->second.GetPicName());
								}
								animeManager.ResetEffect(bgManager.GetBackground());
								systemManager.GameState() = Main;
							}
						}
					}
					//如果是离开主菜单
					else if(systemManager.preState == Main)
					{
						bool finished = true;
						for(map<wstring,Button>::iterator iter = buttonManager.GetButtons(L"Main").begin(); iter != buttonManager.GetButtons(L"Main").end(); iter++)
						{
							iter->second.Cover() = false;
							animeManager.MoveX(iter->second.GetPicName(),iter->second.GetOriginPosX(),iter->second.GetOriginPosX(),1.0f);
							animeManager.MoveY(iter->second.GetPicName(),iter->second.GetOriginPosY(),iter->second.GetOriginPosY()+20,1.0f);
							animeManager.Fade(iter->second.GetPicName(),255,0,1.0f);
							if(animeManager.GetAnime(iter->second.GetPicName()).State() != AFinished)
								finished = false;
						}
						if(finished)
						{
							animeManager.Fade(bgManager.GetBackground(),255,0,1.0f);
							if(animeManager.GetAnime(bgManager.GetBackground()).State() == AFinished)
							{
								//进入下面的阶段
								buttonManager.Show() = false;
								systemManager.preState = Game;
								for(map<wstring,Button>::iterator iter = buttonManager.GetButtons(L"Main").begin(); iter != buttonManager.GetButtons(L"Main").end(); iter++)
								{
									animeManager.ResetEffect(iter->second.GetPicName());
								}
								animeManager.ResetEffect(bgManager.GetBackground());
							}
						}
					}
					//如果是离开读档菜单
					else if(systemManager.preState == Load)
					{
						buttonManager.Show() = false;

						animeManager.Fade(bgManager.GetBackground(),255,0,1.0f);
						if(animeManager.GetAnime(bgManager.GetBackground()).State() == AFinished)
						{
							//进入下面的阶段
							systemManager.preState = Game;
							animeManager.ResetEffect(bgManager.GetBackground());
						}
					}
					//如果是进入游戏
					else if(systemManager.preState == Game)
					{
						//淡入
						buttonManager.Show() = false;
						bgManager.SetBackground(scriptManager.bgName);
						animeManager.Fade(bgManager.GetBackground(),0,255,1.0f);
						if(animeManager.GetAnime(bgManager.GetBackground()).State() == AFinished)
						{
							for(map<wstring,Button>::iterator iter = buttonManager.GetButtons(L"Main").begin(); iter != buttonManager.GetButtons(L"Main").end(); iter++)
							{
								animeManager.ResetEffect(iter->second.GetPicName());
							}
							animeManager.ResetEffect(bgManager.GetBackground());
							bgManager.bTransit = false;
							buttonManager.SetScene("Game");
							systemManager.GameState() = Game;
							if(scriptManager.bInitialized == false)
								scriptManager.bInitialized = true;
							bgm.SetLoop(true);
							if(scriptManager.bBgm)
								bgm.Play();
						}
					}

					//清屏
					window.GetWindow().Clear(sf::Color::White);

					//显示背景
					bgManager.DrawBackground(animeManager,window.GetWindow());

					//显示按钮
					if(systemManager.GameState() != Game && systemManager.preState != Game && systemManager.preState != Load)
						buttonManager.DrawButtons(animeManager,window.GetWindow(),true);

					#ifdef DEBUG
					//显示帧速
					window.DisplayFrameRate(fontManager.GetFont(ini.fontNames[0]));
					#endif

					//显示光栅化
					window.GetWindow().Display();
				}break;
			case Exit:
				{
					//输入F2则截屏
					if(inputManager.IsF2KeyPressed())
						window.SaveScreen();
					
					//获取输入
					inputManager.UpdateInput(window.GetWindow().GetInput());
					wstring buttonInfo = buttonManager.UpdateButtons(inputManager.GetMouseX(),inputManager.GetMouseY());


					//清屏
					window.GetWindow().Clear(sf::Color::White);
					//绘制背景
					bgManager.DrawBackground(animeManager,window.GetWindow());
					//绘制遮罩
					animeManager.DrawAnime("Black",window.GetWindow());
					//绘制提示
					animeManager.DrawAnime(systemManager.exit,window.GetWindow());
					//绘制按钮
					buttonManager.DrawButtons(animeManager,window.GetWindow(),false);

					//如果按下鼠标左键
					if(inputManager.IsMouseLeftPressed())
					{
						if(buttonInfo == L"Exit")
						{
							//记录系统信息
							ofstream outfile("Resources/GameSettings.setting");
							//是否播放背景音乐
							SaveVariable(outfile,scriptManager.bBgm);
							SaveVariable(outfile,systemManager.bgmVolume);
							SaveVariable(outfile,soundManager.bPlay);
							SaveVariable(outfile,soundManager.volume);
							SaveVariable(outfile,scriptManager.bDub);
							SaveVariable(outfile,systemManager.dubVolume);
							SaveVariable(outfile,static_cast<unsigned int>(dialogueManager.GetDialogueColor().r));
							SaveVariable(outfile,static_cast<unsigned int>(dialogueManager.GetDialogueColor().g));
							SaveVariable(outfile,static_cast<unsigned int>(dialogueManager.GetDialogueColor().b));
							SaveVariable(outfile,static_cast<unsigned int>(dialogueManager.GetDialogueColor().a));
							SaveVariable(outfile,static_cast<unsigned int>(dialogueManager.GetTextColor().r));
							SaveVariable(outfile,static_cast<unsigned int>(dialogueManager.GetTextColor().g));
							SaveVariable(outfile,static_cast<unsigned int>(dialogueManager.GetTextColor().b));
							SaveVariable(outfile,static_cast<unsigned int>(dialogueManager.GetTime()));
							outfile.close();
							outfile.clear();

							window.GetWindow().Close();
						}
						else if(buttonInfo == L"Cancel")
						{
							systemManager.GameState() = systemManager.exitState;
							switch(systemManager.exitState)
							{
							case Main:
								{
									buttonManager.SetScene("Main");
								}break;
							case Game:
								{
									buttonManager.SetScene("Game");
								}break;
							case Setting:
								{
									buttonManager.SetScene("Sounds");
								}break;
							case Save:
							case Load:
								{
									buttonManager.SetScene("SaveLoad");
								};break;
							}
						}
					}

					//如果按下ESC或者按下鼠标右键
					if(inputManager.IsMouseRightPressed() || inputManager.IsEscKeyPressed())
					{
						systemManager.GameState() = systemManager.exitState;
						switch(systemManager.exitState)
						{
						case Main:
							{
								buttonManager.SetScene("Main");
							}break;
						case Game:
							{
								buttonManager.SetScene("Game");
							}break;
						case Setting:
							{
								buttonManager.SetScene("Sounds");
							}break;
						case Save:
						case Load:
							{
								buttonManager.SetScene("SaveLoad");
							};break;
						}
					}

					//如果关闭默认鼠标且显示鼠标则显示自定义鼠标
					if(ini.mousePicName != "DEFAULT" && inputManager.ShowMouse())
						inputManager.DrawMouse(animeManager,window.GetWindow());

					//光栅化
					window.GetWindow().Display();
				}break;
			default:
				{
					throw runtime_error("Game state error.");
				}break;
			}
			//获取事件
			while(window.GetWindow().GetEvent(window.GetEvent()))
			{
				//按了关闭按钮
				if(window.GetEvent().Type == sf::Event::Closed)
				{
					if(systemManager.GameState() != Init && systemManager.GameState() != Transit)
					{
						systemManager.exitState = systemManager.GameState();
						systemManager.GameState() = Exit;
						buttonManager.SetScene("Exit");
					}
					else
						window.GetWindow().Close();
				}
			}
		}
	}
	catch (runtime_error err)
	{
		//在控制台输出错误信息
		cerr<<err.what()<<endl;
		system("pause");
	}
	
	return EXIT_SUCCESS;
}