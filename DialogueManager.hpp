//对话框类
//用于显示对话框处理对话内容
//Written by nashdal13
//First Draft: 2012.4.23

#ifndef SYSTEM
	#define SYSTEM
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
#ifndef FONT
	#define FONT
	#include "FontManager.hpp"
#endif
#ifndef BUTTON
	#define BUTTON
	#include "Button.hpp"
#endif
#ifndef BUTTONM
	#define BUTTONM
	#include "ButtonManager.hpp"
#endif

enum TextSpeed{slow,normal,fast};

enum DState{DInit,DRun,DFinished,DChoice,DExit};

class Choice: public Button
{
public:
	void DrawChoice(AnimeManager& animeManager, sf::Color color, sf::Font& font,sf::RenderWindow& window); //绘制选项
	void SetText(const wstring t, const float x, const float y, const float s); //设置文字
	void SetText(const wstring t); //重新设置文字
	wstring GetText(); //获取文字
private:
	wstring text; //文字
	float textX,textY; //文字的位置
	float textSize; //文字的大小
	sf::Color color; //文字颜色
};

class DialogueManager
{
public:
	DialogueManager(ButtonManager& bm); //构造函数

	void Init(const string pic, const string namePic, const string font, const float pX, const float pY, const float pNX, const float pNY, 
		const float mX, const float mY, const float tX, const float tY, const unsigned int maxL, const unsigned int nW, 
		const unsigned int nH, const float size, const unsigned int interval,const float st, const float nt, const float ft, const unsigned int charN, const unsigned int cAlpha, const unsigned int NOC); //初始化

	wstring UpdateChoice(const float x, const float y); //更新选择
	void SetChoice(const wstring content,const wstring jumpMark,const unsigned int n); //设置选项内容
	void DrawDialogue(AnimeManager& animeManager,FontManager& fontManager,sf::RenderWindow& window); //显示对话框和对话内容

	void SetTime(const TextSpeed textSpeed); //设置时间
	void SetContent(const wstring content); //设置对话内容
	void SetName(const wstring name); //设置人名
	void SetColor(const unsigned int r, const unsigned int g, const unsigned int b); //设置文字颜色
	void SetSize(const float size); //设置文字大小
	void SetInterval(const unsigned int interval); //设置文字间距
	void SetFont(const string font); //设置字体
	void SetNameLength(const unsigned int length); //设定人名长度

	TextSpeed GetTime(); //获取播放速度
	sf::Color GetDialogueColor(); //获取背景颜色
	sf::Color GetTextColor(); //获取文字颜色
	wstring GetContent(); //获取对话内容
	wstring GetName(); //获取名字
	unsigned int GetNameLength(); //获取姓名长度
	vector<Choice>& GetChoices(); //获取选项
	unsigned int GetChoiceNum(); //获得选项数量

	void SetBackgroundColor(const unsigned int r, const unsigned int g, const unsigned int b,const unsigned int a); //设置背景色

	bool& ShowDialogue(); //是否显示对话框
	bool& ShowName(); //是否显示人名
	DState& State(); //返回状态
	sf::Clock clock; //记录进入和退出动画时间
private:
	ButtonManager& buttonManager;
	bool bShow; //是否显示对话框
	bool bShowName; //是否显示人名

	vector<Choice> choices; //选项
	unsigned int choiceNum; //激活的选项数量

	string picName; //对话框背景的图片
	float picX,picY; //对话框背景的位置

	string namePicName; //显示人名的图片
	float picNX,picNY; //人名背景的位置
	unsigned int picNWidth,picNHeight; //人名背景的宽度
	unsigned int nameLength; //人名的长度

	string fontName; //文字的字体
	float textX,textY; //文字的位置
	wstring textContent;
	Text text; //对话框内的文字
	unsigned int maxLength; //对话框最大宽度
	float textSize; //文字大小
	unsigned int textInterval; //文字行间隔
	TextSpeed textSpeed; //文字显示速度
	float slowTime,normalTime,fastTime; //显示间隔时间s
	unsigned int charNum;//一次显示的文字数量
	sf::Color color; //文字颜色
	sf::Color diaColor; //对话框背景色

	float nameTX,nameTY; //姓名文字的位置
	wstring nameContent;
	Text nameText; //人的姓名

	float markX,markY; //结束标记的位置
	
	DState state; //状态变量
};