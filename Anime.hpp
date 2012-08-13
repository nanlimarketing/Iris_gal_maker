//Written by nashdal13
//动画类，用于记录动画信息
//First Draft: 2012.3.27
//2012.4.4 Revised: 增加清除接口
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif
#ifndef IMAGE
	#define IMAGE
	#include "ImageManager.hpp"
#endif

enum AnimeState{AInit,ARun,AFinished};

class Anime
{
public:
	Anime(); //默认构造函数
	Anime(const string name, const vector<string> img, ImageManager& imgManager); //从图像管理器中初始化动画
	Anime(const string name, const string img, ImageManager& imgManager); //从图像管理器中初始化图片
	~Anime(); //析构函数
	
	void SetName(const string name); //设置动画名

	void SetImage(const vector<string> img, ImageManager& imgManager); //从图像管理器中设置动画
	void SetImage(unsigned int frameIndex, string img, ImageManager& imgManager); //未某一帧设置图像

	void SetInterval(const float interval, const unsigned int frameIndex = 0); //为某一帧设置间隔
	void SetIntervalAll(const float interval); //为所有帧设置时间间隔

	void SetPosition(const float posX, const float posY, const unsigned int frameIndex = 0); //为某一帧设置位置
	void SetPositionAll(const float posX, const float posY); //为所有帧设置位置
	void SetPositionXAll(const float posX);
	void SetPositionYAll(const float posX);

	void SetCenter(const float posX, const float posY, const unsigned int frameIndex = 0); //为某一帧设置中心
	void SetCenterAll(const float posX, const float posY); //为所有帧设置中心

	void SetRotation(const float angle, const unsigned int frameIndex = 0); //为某一帧设置旋转
	void SetRotationAll(const float angle); //为所有帧设置旋转

	void SetScale(const float scaleX, const float scaleY, const unsigned int frameIndex = 0); //为某一帧设置缩放
	void SetScaleAll(const float scaleX, const float scaleY); //为所有帧设置缩放
	void SetScaleXAll(const float scaleX);
	void SetScaleYAll(const float scaleY);

	void SetMove(const float moveX, const float moveY, const unsigned int frameIndex = 0); //为某一帧设置位移
	void SetMoveAll(const float moveX, const float moveY); //为所有帧设置位移

	void SetAlpha(const unsigned int alpha, const unsigned int frameIndex = 0); //为某一帧设置alpha值
	void SetAlphaAll(const unsigned int alpha); //为所有帧设置Alpha值

	const unsigned int GetTotalIndex(); //获得总帧数
	
	unsigned int& CurIndex(); //当前的帧数
	
	const string GetName(); //获得动画名
	const vector<string> GetImgNames(); //获得图片的名称数组
	const float GetInterval(unsigned int frameIndex); //获得指定帧间隔
	const float GetCurInterval(); //获得当前帧间隔
	
	void SetRepeat(bool bRe); //是否循环播放
	bool GetRepeat();
	
	sf::Clock& Clock(); //返回时间
	AnimeState& State(); //返回状态
	bool& FadeInitEffect();
	bool& MoveXInitEffect();
	bool& MoveYInitEffect();
	bool& ScaleXInitEffect();
	bool& ScaleYInitEffect();
	bool& RotateInitEffect();
	bool& FadeOut();

	sf::Sprite& GetCurSprite(); //返回当前的精灵
	sf::Sprite& GetSprite(unsigned int frameIndex); //返回指定帧
	sf::Sprite& operator[](unsigned int frameIndex); //用下标返回指定帧
private:
	string animeName; //动画的名字

	unsigned int totalIndex; //记录有几帧
	unsigned int curIndex; //记录当前是第几帧

	vector<pair<sf::Sprite, float>> sprites;//记录精灵信息和记录时间
	vector<string> imgNames; //记录使用的图像的名称

	sf::Clock clock; //记录显示间隔时间
	AnimeState state;

	bool bRepeat; //是否循环播放
	bool bFadeInitEffect;
	bool bMoveXInitEffect;
	bool bMoveYInitEffect;
	bool bRotateInitEffect;
	bool bScaleXInitEffect;
	bool bScaleYInitEffect;
	bool bFadeOut;
};
