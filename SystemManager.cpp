//Written by nashdal13
//系统类，用于封装系统对象，并负责初始化系统对象
//包括初始化鼠标，初始化片头logo和初始化主界面
#include "SystemManager.hpp"

SystemManager::SystemManager(InitManager& initM, ImageManager& imageM, AnimeManager& animeM, FontManager& fontM, InputManager& inputM, DialogueManager& dialogueM, CharacterManager& characterM, SoundManager& soundM, ButtonManager& buttonM, FileManager& fileM, ScriptManager& scriptM):
	initManager(initM),imageManager(imageM),animeManager(animeM),fontManager(fontM),inputManager(inputM),dialogueManager(dialogueM),characterManager(characterM),soundManager(soundM),buttonManager(buttonM),fileManager(fileM),scriptManager(scriptM)
{
	gameState = Init;
	bInitialized = false;
	bgmVolume = 100.0f;
	dubVolume = 100.0f;
}

void SystemManager::Logo()
{
	//初始化LOGO的图片信息
	imageManager.LoadImage(initManager.logoPicName);
	Anime logo("LOGO",initManager.logoPicName,imageManager);
	//居中
	sf::Vector2f vec = logo[0].GetSize();
	logo.SetCenter(vec.x/2,vec.y/2);
	logo.SetPosition(static_cast<float>(initManager.width/2),static_cast<float>(initManager.height/2));
	//存储
	animeManager.PushAnime(logo);
	clock.Reset();
}

void SystemManager::DrawLogo(sf::RenderWindow& window)
{
	//绘制开场LOGO
	if(clock.GetElapsedTime() < initManager.logoAlphaTime)
	{
		//淡入
		//以用户指定的颜色清屏
		window.Clear(initManager.color);
		float step = static_cast<float>(255/initManager.logoAlphaTime); //每秒alpha变化值
		//设置透明度
		animeManager.GetAnime("LOGO").SetAlpha(static_cast<unsigned int>(step*clock.GetElapsedTime())); //变化alpha
		//绘制LOGO
		animeManager.DrawAnime("LOGO",window);
		//显示屏幕
		window.Display();
	}
	else if(clock.GetElapsedTime() > initManager.logoTime-initManager.logoAlphaTime && clock.GetElapsedTime() <= initManager.logoTime)
	{
		//淡出
		//以用户指定的颜色清屏
		window.Clear(initManager.color);
		float step = static_cast<float>(255/initManager.logoAlphaTime); //每秒alpha变化值
		//设置透明度
		animeManager.GetAnime("LOGO").SetAlpha(static_cast<unsigned int>
			(255-step*(clock.GetElapsedTime()-(initManager.logoTime-initManager.logoAlphaTime)))); //变化alpha
		//绘制LOGO
		animeManager.DrawAnime("LOGO",window);
		//显示屏幕
		window.Display();
	}
	else if(clock.GetElapsedTime() > initManager.logoTime)
	{	
		//以用户指定的颜色清屏
		window.Clear(initManager.color);
		//显示屏幕
		window.Display();
		//保证初始化进程没有结束
		Wait();
		//清除LOGO图像
		animeManager.ClearAnime("LOGO",imageManager);
		//进入主菜单
		gameState = Transit;
		preState = Init;
	}
	else
	{
		//显示
		//以用户指定的颜色清屏
		window.Clear(initManager.color);
		//设置透明度
		animeManager.GetAnime("LOGO").SetAlpha(255); //全不透明
		//绘制LOGO
		animeManager.DrawAnime("LOGO",window);
		//显示屏幕
		window.Display();
	}
}

void SystemManager::Initialize()
{
	//开始多线程进行初始化
	if(bInitialized == false)
	{
		Launch();
		bInitialized = true;
	}
}

State& SystemManager::GameState()
{
	return gameState;
}

string SystemManager::SystemFont()
{
	return sysFont;
}

void SystemManager::Run()
{
	//载入资源
	sysFont = initManager.fontNames[0]; //第一个载入的字体为系统字体
	//如需要则读入鼠标图片
	if(initManager.mousePicName != "DEFAULT")
	{
		imageManager.LoadImage(initManager.mousePicName);
		Anime mouse("Mouse",initManager.mousePicName,imageManager);
		animeManager.PushAnime(mouse);
	}

	//从资源文件读入游戏资源
	ifstream infile(initManager.resourceFileName);
	if(!infile)
		throw runtime_error("Cannot find the resource file: "+initManager.resourceFileName);

	string fileName;
	string com_name;

	while(!infile.eof())
	{
		ReadVariable(infile, com_name);

		if(com_name == "Main_Menu")
		{
			//读取主菜单资源
			ReadVariable(infile,fileName);

			//打开主菜单设定文件
			ifstream file;
			file.open(fileName);

			while(!file.eof())
			{
				ReadVariable(file,com_name);

				if(com_name == "Background")
				{
					ReadVariable(file,mainBg);
					animeManager.AddAnime(mainBg,mainBg,imageManager);
				}
				else if(com_name == "Add_Button")
					CreateButton(file,L"Main");
				else if(com_name == "#")
					JumpOneVariable(file);
			}

			file.close();
			file.clear();
		}
		else if(com_name == "Game_Menu")
		{
			//读取游戏中资源
			ReadVariable(infile,fileName);

			//打开游戏中菜单设定文件
			ifstream file;
			file.open(fileName);

			while(!file.eof())
			{
				ReadVariable(file,com_name);

				if(com_name == "Add_Button")
					CreateButton(file,L"Game");
				else if(com_name == "#")
					JumpOneVariable(file);
			}

			file.close();
			file.clear();
		}
		else if(com_name == "Exit_Menu")
		{
			//读取退出菜单资源
			ReadVariable(infile,fileName);

			//打开退出菜单设定文件
			ifstream file;
			file.open(fileName);

			//全屏遮罩
			imageManager.CreateImage("Black",initManager.width,initManager.height,sf::Color::Black);
			Anime blackScreen("Black","Black",imageManager);
			blackScreen.GetCurSprite().SetColor(sf::Color(255,255,255,100));
			animeManager.PushAnime(blackScreen);

			while(!file.eof())
			{
				file>>com_name;
				if(com_name == "Notice")
				{
					//读取提示
					ReadVariable(file,exit);
					animeManager.AddAnime(exit,exit,imageManager);
					//居中
					sf::Vector2f vec = animeManager.GetAnime(exit)[0].GetSize();
					animeManager.GetAnime(exit).SetCenter(vec.x/2,vec.y/2);
					animeManager.GetAnime(exit).SetPosition(static_cast<float>(initManager.width/2),static_cast<float>(initManager.height/2));
				}
				else if(com_name == "Add_Button")
					CreateButton(file,L"Exit");
			}

			file.close();
			file.clear();
		}
		else if(com_name == "Setting_Menu")
		{
			//读取设定菜单资源
			ReadVariable(infile,fileName);

			//打开游戏中菜单设定文件
			ifstream file;
			file.open(fileName);

			while(!file.eof())
			{
				ReadVariable(file,com_name);

				if(com_name == "Setting_Background")
				{
					ReadVariable(file,setBg);
					animeManager.AddAnime(setBg,setBg,imageManager);
				}
				else if(com_name == "Add_Setting_Button")
					CreateButton(file,L"Setting");
				else if(com_name == "Add_Sound_Button")
					CreateButton(file,L"Sounds");
				else if(com_name == "Sound_Background")
				{
					ReadVariable(file,sounds);

					float x,y;
					animeManager.AddAnime(sounds,sounds,imageManager);
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					animeManager.GetAnime(sounds).SetPositionAll(x,y);
				}
				else if(com_name == "Set_Sound_Positions")
				{
					float x,y;
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					bgmVol.SetPosition(x,y);
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					sfxVol.SetPosition(x,y);
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					dubVol.SetPosition(x,y);
				}
				else if(com_name == "Add_Dialogue_Button")
					CreateButton(file,L"Dialogue");
				else if(com_name == "Dialogue_Background")
				{
					ReadVariable(file,dialogue);
					animeManager.AddAnime(dialogue,dialogue,imageManager);
					float x,y;
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					animeManager.GetAnime(dialogue).SetPositionAll(x,y);
				}
				else if(com_name == "Set_Dialogue_Positions")
				{
					float x,y;
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					red.SetPosition(x,y);
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					green.SetPosition(x,y);
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					blue.SetPosition(x,y);
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					alpha.SetPosition(x,y);
				}
				else if(com_name == "Add_Text_Button")
					CreateButton(file,L"Text");
				else if(com_name == "Text_Background")
				{
					ReadVariable(file,text);
					float x,y;
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					animeManager.AddAnime(text,text,imageManager);
					animeManager.GetAnime(text).SetPositionAll(x,y);
				}
				else if(com_name == "Set_Text_Positions")
				{
					float x,y;
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					tRed.SetPosition(x,y);
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					tGreen.SetPosition(x,y);
					x = ReadFloat(file,true);
					y = ReadFloat(file,true);
					tBlue.SetPosition(x,y);
				}
				else if(com_name == "#")
					JumpOneVariable(file);
			}

			file.close();
			file.clear();
		}
		else if(com_name == "Save_Menu")
		{
			//读取存储资源
			ReadVariable(infile,fileName);

			//打开存储设定文件
			ifstream file;
			file.open(fileName);

			while(!file.eof())
			{
				ReadVariable(file,com_name);

				if(com_name == "Background")
				{
					ReadVariable(file,saveBg);
					animeManager.AddAnime(saveBg,saveBg,imageManager);
				}
				else if(com_name == "Add_Button")
					CreateButton(file,L"SaveLoad");
				else if(com_name == "Add_File_Button")
					CreateFileButton(file,scale,pos_x,pos_y);
				else if(com_name == "Pic_Scale")
					ReadVariable(file,scale);
				else if(com_name == "Pic_Position_X")
					ReadVariable(file,pos_x);
				else if(com_name == "Pic_Position_Y")
					ReadVariable(file, pos_y);
				else if(com_name == "#")
					JumpOneVariable(file);
			}

			file.close();
			file.clear();
		}
		else if(com_name == "Load_Menu")
		{
			//读取存储资源
			ReadVariable(infile,fileName);

			//打开存储设定文件
			ifstream file;
			file.open(fileName);

			while(!file.eof())
			{
				ReadVariable(file,com_name);

				if(com_name == "Background")
				{
					ReadVariable(file,loadBg);
					animeManager.AddAnime(loadBg,loadBg,imageManager);
				}
				else if(com_name == "#")
					JumpOneVariable(file);
			}

			file.close();
			file.clear();
		}
		else if(com_name == "Game_Settings")
		{
			//读入系统设定
			ReadVariable(infile,fileName);

			ifstream file;
			file.open(fileName);

			scriptManager.bBgm = ReadBool(file,false);
			bgmVolume = ReadFloat(file,false);
			soundManager.bPlay = ReadBool(file,false);
			soundManager.volume = ReadFloat(file,false);
			scriptManager.bDub = ReadBool(file,false);
			dubVolume = ReadFloat(file,false);
			unsigned int r,g,b,a;
			ReadVariable(file,r);
			ReadVariable(file,g);
			ReadVariable(file,b);
			ReadVariable(file,a);
			dialogueManager.SetBackgroundColor(r,g,b,a);
			ReadVariable(file,r);
			ReadVariable(file,g);
			ReadVariable(file,b);
			dialogueManager.SetColor(r,g,b);
			dialogueManager.SetTime(TextSpeed(ReadUnsignedInt(file,false)));

			file.close();
			file.clear();

		}
		else if(com_name == "Game_Script")
		{
			ReadVariable(infile,fileName);
			//初始化主脚本
			scriptManager.Init(fileName);
		}
		else if(com_name == "Add_Background")
		{
			string picName;
			ReadVariable(infile, picName);
			animeManager.AddAnime(picName,picName,imageManager);
		}
		else if(com_name == "Set_Dialogue_Box")
		{
			string diaName,namePic,fontName;
			unsigned int pWidth,pHeight,pNWidth,pNHeight,maxL,interval,charNum,NOC,cWidth,cHeight,cAlpha;
			float size,st,nt,ft,pX,pY,pNX,pNY,mX,mY,tX,tY;
			do
			{
				infile>>com_name;
				if(com_name == "Frame_Pic")
				{
					ReadVariable(infile,diaName);
					animeManager.AddAnime(diaName,diaName,imageManager);
				}
				else if(com_name == "Name_Pic")
				{
					ReadVariable(infile,namePic);
					animeManager.AddAnime(namePic,namePic,imageManager);
				}
				else if(com_name == "Font")
					ReadVariable(infile,fontName);
				else if(com_name == "Frame_X")
					ReadVariable(infile,pX);
				else if(com_name == "Frame_Y")
					ReadVariable(infile,pY);
				else if(com_name == "Frame_Width")
					ReadVariable(infile,pWidth);
				else if(com_name == "Frame_Height")
					ReadVariable(infile,pHeight);
				else if(com_name == "Name_X")
					ReadVariable(infile,pNX);
				else if(com_name == "Name_Y")
					ReadVariable(infile,pNY);
				else if(com_name == "Name_Width")
					ReadVariable(infile,pNWidth);
				else if(com_name == "Name_Height")
					ReadVariable(infile,pNHeight);
				else if(com_name == "End_Mark_X")
					ReadVariable(infile,mX);
				else if(com_name == "End_Mark_Y")
					ReadVariable(infile,mY);
				else if(com_name == "Text_X")
					ReadVariable(infile,tX);
				else if(com_name == "Text_Y")
					ReadVariable(infile,tY);
				else if(com_name == "Max_Length")
					ReadVariable(infile,maxL);
				else if(com_name == "Font_Size")
					ReadVariable(infile,size);
				else if(com_name == "Text_Interval")
					ReadVariable(infile,interval);
				else if(com_name == "Slow_Time")
					ReadVariable(infile,st);
				else if(com_name == "Normal_Time")
					ReadVariable(infile,nt);
				else if(com_name == "Fast_Time")
					ReadVariable(infile,ft);
				else if(com_name == "Chars_Per_Show")
					ReadVariable(infile,charNum);
				else if(com_name == "Choice_Cover_Width")
					ReadVariable(infile,cWidth);
				else if(com_name == "Choice_Cover_Height")
					ReadVariable(infile,cHeight);
				else if(com_name == "Choice_Cover_Alpha")
					ReadVariable(infile,cAlpha);
				else if(com_name == "Max_Choices")
					ReadVariable(infile,NOC);
				else if(com_name == "End_Set")
				{
					//建立背景图片
					imageManager.CreateImage("diaBg",pWidth,pHeight,sf::Color(255,255,255));
					Anime diaBg("diaBg","diaBg",imageManager);
					animeManager.PushAnime(diaBg);
					//建立姓名背景
					imageManager.CreateImage("nameBg",pNWidth,pNHeight,sf::Color(255,255,255));
					Anime nameBg("nameBg","nameBg",imageManager);
					animeManager.PushAnime(nameBg);
					//建立选择遮罩图片
					imageManager.CreateImage("cover",cWidth,cHeight,sf::Color(255,255,255,100));
					Anime cover("cover","cover",imageManager);
					animeManager.PushAnime(cover);
					//初始化对话框
					dialogueManager.Init(diaName,namePic,fontName,pX,pY,pNX,pNY,mX,mY,tX,tY,maxL,pNWidth,pNHeight,size,interval,st,nt,ft,charNum,cAlpha,NOC);
				}
			}
			while(com_name != "End_Set");
		}
		else if(com_name == "Add_Sound")
		{
			soundManager.LoadSound(ReadString(infile,false));
		}
		else if(com_name == "Add_Character")
			CreateAnime(infile);
		else if(com_name == "Add_Anime")
			CreateAnime(infile);
		else if(com_name == "#")
			JumpOneVariable(infile);
	}

	//关闭文件
	infile.close();
	infile.clear();
}

void SystemManager::CreateAnime(ifstream& file)
{
	string com_name;
	string anime_name;
	vector<string> frame_names;
	vector<float> intervals;
	bool bRepeat = false;
	do
	{
		file>>com_name;
		if(com_name == "Set_Name")
			ReadVariable(file,anime_name);
		else if(com_name == "Set_Loop")
			bRepeat = true;
		else if(com_name == "Add_Frame")
			frame_names.push_back(ReadString(file,false));
		else if(com_name == "Add_Interval")
			intervals.push_back(ReadFloat(file,false));
		else if(com_name == "End_Add")
		{
			imageManager.LoadImages(frame_names);
			Anime temp(anime_name,frame_names,imageManager);
			temp.SetRepeat(bRepeat);
			for(unsigned int i = 0; i < intervals.size(); i++)
			{
				temp.SetInterval(intervals[i],i);
			}
			animeManager.PushAnime(temp);
		}
	}
	while(com_name != "End_Add");
}

void SystemManager::CreateButton(ifstream& file, wstring scene)
{
	string com_name;
	string picN,coverN,clickedCN,clickedN,info;
	float pX,pY,cX,cY,bX,bY;
	unsigned int alpha,bW,bH;

	do
	{
		ReadVariable(file,com_name);

		if(com_name == "End_Add_Button")
		{
			//添加按钮
			buttonManager.AddButton(scene,StringToWString(info),picN,coverN,clickedCN,clickedN,pX,pY,cX,cY,alpha,bX,bY,bW,bH);
		}
		else if(com_name == "Info")
			ReadVariable(file,info);
		else if(com_name == "Pic_Name")
		{
			ReadVariable(file,picN);
			animeManager.AddAnime(picN,picN,imageManager);
		}
		else if(com_name == "Cover_Name")
		{
			ReadVariable(file,coverN);
			animeManager.AddAnime(coverN,coverN,imageManager);
		}
		else if(com_name == "Clicked_Cover_Name")
		{
			ReadVariable(file,clickedCN);
			animeManager.AddAnime(clickedCN,clickedCN,imageManager);
		}
		else if(com_name == "Clicked_Name")
		{
			ReadVariable(file,clickedN);
			animeManager.AddAnime(clickedN,clickedN,imageManager);
		}
		else if(com_name == "Pic_X")
			ReadVariable(file,pX);
		else if(com_name == "Pic_Y")
			ReadVariable(file,pY);
		else if(com_name == "Cover_X")
			ReadVariable(file,cX);
		else if(com_name == "Cover_Y")
			ReadVariable(file,cY);
		else if(com_name == "Cover_Alpha")
			ReadVariable(file,alpha);
		else if(com_name == "Button_X")
			ReadVariable(file,bX);
		else if(com_name == "Button_Y")
			ReadVariable(file,bY);
		else if(com_name == "Button_Width")
			ReadVariable(file,bW);
		else if(com_name == "Button_Height")
			ReadVariable(file,bH);
	}
	while(com_name != "End_Add_Button");
}

void SystemManager::CreateFileButton(ifstream& file, float scale, float pos_x, float pos_y)
{
	string com_name;
	string picN,coverN,clickedCN,clickedN,info;
	float pX,pY,cX,cY,bX,bY,textSize,tX,tY;
	unsigned int alpha,bW,bH;
	wstring text;

	do
	{
		ReadVariable(file,com_name);

		if(com_name == "End_Add_Button")
		{
			//添加按钮
			fileManager.AddFileButton(StringToWString(info),picN,coverN,clickedCN,clickedN,pX,pY,cX,cY,alpha,bX,bY,bW,bH);
			fileManager.SetTextSize(textSize);
			fileManager.SetText(StringToWString(info),tX,tY,text);
		}
		else if(com_name == "Button_Text_Size")
			ReadVariable(file,textSize);
		else if(com_name == "Info")
		{
			ReadVariable(file,info);
			//顺便读取存档图片文件
			string filePath = "Save/";
			wifstream infile;
			infile.open(filePath+info+".sav");
			//如果存档存在
			if(infile)
			{
				animeManager.AddAnime(info,filePath+info+".jpg",imageManager);
				animeManager.GetAnime(info).SetScaleAll(scale,scale);
				animeManager.GetAnime(info).SetPositionAll(pos_x,pos_y);
			}
			infile.close();
			infile.clear();
		}
		else if(com_name == "Pic_Name")
		{
			ReadVariable(file,picN);
			animeManager.AddAnime(picN,picN,imageManager);
		}
		else if(com_name == "Cover_Name")
		{
			ReadVariable(file,coverN);
			animeManager.AddAnime(coverN,coverN,imageManager);
		}
		else if(com_name == "Clicked_Cover_Name")
		{
			ReadVariable(file,clickedCN);
			animeManager.AddAnime(clickedCN,clickedCN,imageManager);
		}
		else if(com_name == "Clicked_Name")
		{
			ReadVariable(file,clickedN);
			animeManager.AddAnime(clickedN,clickedN,imageManager);
		}
		else if(com_name == "Pic_X")
			ReadVariable(file,pX);
		else if(com_name == "Pic_Y")
			ReadVariable(file,pY);
		else if(com_name == "Cover_X")
			ReadVariable(file,cX);
		else if(com_name == "Cover_Y")
			ReadVariable(file,cY);
		else if(com_name == "Cover_Alpha")
			ReadVariable(file,alpha);
		else if(com_name == "Button_X")
			ReadVariable(file,bX);
		else if(com_name == "Button_Y")
			ReadVariable(file,bY);
		else if(com_name == "Button_Width")
			ReadVariable(file,bW);
		else if(com_name == "Button_Height")
			ReadVariable(file,bH);
		else if(com_name == "Button_Text")
		{
			wifstream infile;
			infile.imbue(locale(".936"));
			string filePath = "Save/";
			infile.open(filePath+info+".sav");

			if(!infile)
				text = L"Empty";
			else
				getline(infile,text);

			infile.close();
			infile.clear();
		}
		else if(com_name == "Text_X")
			ReadVariable(file,tX);
		else if(com_name == "Text_Y")
			ReadVariable(file,tY);
	}
	while(com_name != "End_Add_Button");
}