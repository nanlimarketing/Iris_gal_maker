//Written by nashdal13
//输入类，用于处理输入
//First Draft: 2012.3.26
//2012.4.3 Revised: 增加绘制鼠标

#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif
#ifndef ANIMEM
	#define ANIMEM
	#include "AnimeManager.hpp"
#endif
#ifndef WINDOW
	#define WINDOW
	#include "WindowManager.hpp"
#endif

class InputManager
{
public:
	InputManager();
	
	void UpdateInput(const sf::Input& input); //更新输入信息
	
	bool IsEscKeyPressed(); //ESC键是否按下
	bool IsF2KeyPressed();	//F2键是否按下
	bool IsSpaceKeyPressed(); //空格键是否按下
	bool IsMouseLeftPressed(); //是否按下鼠标左键
	bool IsMouseRightPressed(); //是否按下鼠标右键

	bool IsMouseLeftDown(); //是否一直按着鼠标左键

	float GetMouseX(); //鼠标的X位置
	float GetMouseY(); //鼠标的Y位置

	bool& ShowMouse(); //是否显示鼠标
	void DrawMouse(AnimeManager& animeManager, sf::RenderWindow& window); // 绘制鼠标
private:
	bool mouseState;
	bool SpaceKeyPressed;
	bool SpaceKeyDown;
	bool ESCKeyPressed;
	bool ESCKeyDown;
	bool F2KeyPressed;
	bool F2KeyDown;
	bool LBMousePressed;
	bool LBMouseDown;
	bool RBMousePressed;
	bool RBMouseDown;
	float mouseX; //记录鼠标X位置
	float mouseY; //记录鼠标Y位置
};
