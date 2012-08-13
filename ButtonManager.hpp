//管理桌面所有按钮
//Written by nashdal13
//First Draft: 2012.5.1

#ifndef SYS
	#define SYS
	#include "System.hpp"
#endif

#ifndef BUTTON
	#define BUTTON
	#include "Button.hpp"
#endif
#ifndef ANIMEM
	#define ANIMEM
	#include "AnimeManager.hpp"
#endif
#ifndef FONT
	#define FONT
	#include "FontManager.hpp"
#endif

class ButtonManager
{
public:
	ButtonManager();
	void AddButton(const wstring scene, Button button); //初始化增加按钮
	void AddButton(const wstring scene, const wstring info, const string picN, const string coverN, const string coverCN, const string clickedN, const float pX, 
		const float pY, const float cX, const float cY, unsigned int a, const float bX, const float bY,
		const unsigned int bW, const unsigned int bH);
	wstring UpdateButtons(const float x, const float y); //更新按钮状态
	void SetScene(const string scene); //设置当前状态
	string GetScene(); //返回当前状态
	void DrawButtons(AnimeManager& animeManager, sf::RenderWindow& window, bool bEffect); //绘制按钮
	bool& Show(); //显示
	Button& GetButton(const wstring scene,const wstring name);
	map<wstring,Button>& GetButtons(const wstring scene);
private:
	bool bShow;
	string curScene;
	map<wstring, Button> settingButtons;
	map<wstring, Button> soundsButtons;
	map<wstring, Button> dialogueButtons;
	map<wstring, Button> textButtons;
	map<wstring, Button> gameButtons;
	map<wstring, Button> mainButtons;
	map<wstring, Button> exitButtons;
	map<wstring, Button> slButtons;
};