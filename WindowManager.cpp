//Written by nashdal13
//窗体类，用于管理窗体
#include "WindowManager.hpp"

//构造函数
WindowManager::WindowManager(const unsigned int width = 800, const unsigned int height = 600,
						const unsigned int bpp = 32, const string windowName = "", const string windowFlag = "",const string iconName = "", const string mousePicName = "")
{
	//读入图标
	sf::Image image;
	image.LoadFromFile(iconName);

	//记录显示模式
	sf::VideoMode mode(width,height,bpp);
	
	//根据选择的模式建立窗口
	if(windowFlag == "RESIZE")
		mainWindow.Create(mode,windowName.c_str());
	else if (windowFlag == "FULL_SCREEN")
		mainWindow.Create(mode,windowName.c_str(),sf::Style::Fullscreen);
	else
		mainWindow.Create(mode,windowName.c_str(),sf::Style::Close);

	//设置图标
	mainWindow.SetIcon(image.GetWidth(),image.GetHeight(),image.GetPixelsPtr());

	//如果使用自定义鼠标，则不显示原鼠标
	if(mousePicName != "DEFAULT")
		mainWindow.ShowMouseCursor(false);

	//设置窗口位置
#ifdef WIN
	int posX = GetSystemMetrics(SM_CXSCREEN);
	int posY = GetSystemMetrics(SM_CYSCREEN);
#endif
	mainWindow.SetPosition((posX-width)/2,(posY-height)/2);
	
	mainWindow.UseVerticalSync(true); //强制打开垂直同步
	mainWindow.Clear();
}


	
//获得窗体
sf::RenderWindow& WindowManager::GetWindow()
{
	return mainWindow;
}

//获得事件
sf::Event& WindowManager::GetEvent()
{
	return event;
}

void WindowManager::SaveScreen()
{
	sf::Image Screen = mainWindow.Capture();
	string filePath = "Screenshots/";
	string date = GetDate();
	string month(date.begin(),date.begin()+2);
	string day(date.begin()+3,date.begin()+5);
	string time = GetTime();
	string hour(time.begin(),time.begin()+2);
	string min(time.begin()+3,time.begin()+5);
	string second = GetSecond();
	Screen.SaveToFile(filePath+month+day+hour+min+second+".jpg");
}

void WindowManager::SaveScreen(string filePath, string fileName)
{
	sf::Image Screen = mainWindow.Capture();
	Screen.SaveToFile(filePath+"/"+fileName+".jpg");
}

void WindowManager::DisplayFrameRate(sf::Font& font,const float x, const float y)
{
	//计算帧数
	float Framerate = 1.f / mainWindow.GetFrameTime();
	
	//将浮点数转换为字符串
	wstring sFramerate;
	wstringstream ss;
	ss << Framerate;
	ss >> sFramerate;
	
	Text text;
	text.SetPosition(x,y);
	text.SetColor(0,0,0);
	wstring output = L"帧速：";
	output += sFramerate;
	text.SetText(output);
	
	text.DrawText(mainWindow,font);
}