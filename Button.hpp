//按钮类
//用于选择和跳转
//First Draft: 2012.4.26

#ifndef SYS
	#define SYS
	#include "System.hpp"
#endif

#ifndef TEXT
	#define TEXT
	#include "Text.hpp"
#endif
#ifndef ANIMEM
	#define ANIMEM
	#include "AnimeManager.hpp"
#endif

class Button
{
public:
	Button(); //构造函数
	bool OnButton(const float x, const float y); //检测按钮的状态，鼠标是否在按钮上
	void Init(const string picN, const string coverN, const string coverCN, const string clickedN, const float pX, const float pY, const float cX, 
		const float cY, unsigned int a, const float bX, const float bY,const unsigned int bW, const unsigned int bH); //初始化
	void SetPositionX(const float x); //设置图片位置
	void SetPositionY(const float y);
	float GetPositionX();
	float GetPositionY();
	float GetOriginPosX();
	float GetOriginPosY();
	string GetPicName(); //返回图片名称
	void DrawButton(AnimeManager& animeManager, sf::RenderWindow& window, bool bEffect); //绘制按钮
	void SetInfo(const wstring); //设置返回的Info
	wstring GetInfo(); //获得返回的信息
	bool& Clicked();
	bool& Cover();
	
private:
	wstring info; //返回的信息
	bool bShowCover; //是否显示遮罩
	bool bClicked; //按钮是否已经按下
	string picName; //按钮图片
	string clickedName; //按下按钮的图片
	string coverName; //遮罩图片
	string clickedCoverName; //按下按钮的图片
	unsigned int alpha; //遮罩图片的透明度
	float picX,picY; //图片的位置
	float oriPicX,oriPicY; //图片的初始位置
	float coverX,coverY; //遮罩的位置
	float buttonX,buttonY; //按钮判定的位置
	unsigned int buttonHeight,buttonWidth; //按钮判定的区域
};