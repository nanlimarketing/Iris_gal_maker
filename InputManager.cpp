//Written by nashdal13
//输入类，用于处理输入
#include "InputManager.hpp"

InputManager::InputManager()
{
	mouseState = true;
	ESCKeyPressed = false;
	ESCKeyDown = false;
	F2KeyPressed = false;
	F2KeyDown =false;
	SpaceKeyPressed = false;
	SpaceKeyDown = false;
	LBMousePressed = false;
	LBMouseDown = false;
	mouseX = 0;
	mouseY = 0;
}

void InputManager::UpdateInput(const sf::Input& input)
{
	//首先判断是否是按了按键后已松开
	if(SpaceKeyPressed && input.IsKeyDown(sf::Key::Space) == false)
		SpaceKeyPressed = false;
	if(ESCKeyPressed && input.IsKeyDown(sf::Key::Escape) == false)
		ESCKeyPressed = false;
	if(F2KeyPressed && input.IsKeyDown(sf::Key::F2) == false)
		F2KeyPressed = false;
	if(LBMousePressed && input.IsMouseButtonDown(sf::Mouse::Left) == false)
		LBMousePressed = false;
	if(RBMousePressed && input.IsMouseButtonDown(sf::Mouse::Right) == false)
		RBMousePressed = false;
	//再判断是否是按下再松开的状态，如是则认定按了按键
	if(SpaceKeyDown && input.IsKeyDown(sf::Key::Space) == false)
		SpaceKeyPressed = true;
	if(ESCKeyDown && input.IsKeyDown(sf::Key::Escape) == false)
		ESCKeyPressed = true;
	if(F2KeyDown && input.IsKeyDown(sf::Key::F2) == false)
		F2KeyPressed = true;
	if(LBMouseDown && input.IsMouseButtonDown(sf::Mouse::Left) == false)
		LBMousePressed = true;
	if(RBMouseDown && input.IsMouseButtonDown(sf::Mouse::Right) == false)
		RBMousePressed = true;
	//刷新输入状态
	SpaceKeyDown = input.IsKeyDown(sf::Key::Space);
	ESCKeyDown = input.IsKeyDown(sf::Key::Escape);
	F2KeyDown = input.IsKeyDown(sf::Key::F2);
	LBMouseDown = input.IsMouseButtonDown(sf::Mouse::Left);
	RBMouseDown = input.IsMouseButtonDown(sf::Mouse::Right);
	mouseX = static_cast<float>(input.GetMouseX());
	mouseY = static_cast<float>(input.GetMouseY());
}

bool InputManager::IsEscKeyPressed()
{
	return ESCKeyPressed;
}

bool InputManager::IsSpaceKeyPressed()
{
	return SpaceKeyPressed;
}

bool InputManager::IsF2KeyPressed()
{
	return F2KeyPressed;
}

bool InputManager::IsMouseLeftPressed()
{
	return LBMousePressed;
}

bool InputManager::IsMouseRightPressed()
{
	return RBMousePressed;
}

bool InputManager::IsMouseLeftDown()
{
	return LBMouseDown;
}

float InputManager::GetMouseX()
{
	return mouseX;
}
float InputManager::GetMouseY()
{
	return mouseY;
}

bool& InputManager::ShowMouse()
{
	return mouseState; 
}

void InputManager::DrawMouse(AnimeManager& animeManager,sf::RenderWindow& window)
{
	//赋值位置
	animeManager.GetAnime("Mouse").SetPosition(static_cast<float>(mouseX),static_cast<float>(mouseY));
	//绘制鼠标
	animeManager.DrawAnime("Mouse",window);
}
