//人物类，负责处理人物的动作
//Written by nashdal13
//First Draft: 2012.4.25
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif
#ifndef ANIMEM
	#define ANIMEM
	#include "AnimeManager.hpp"
#endif

enum CState{CIn,CShow,COut};

class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();
	bool& ShowCharacter(); //是否显示人物
	void SetCharacter(const string name,const float x, const float y);  //设置播放的角色和位置
	map<string,sf::Vector2f>& GetCharacters(); //返回人物
	void DrawCharacter(AnimeManager& animeManager, sf::RenderWindow& window); //绘制角色

	void FadeIn(const string name,AnimeManager& animeManager); //淡入
	void FadeOut(const string name,AnimeManager& animeManager); //淡出
	void ClearCharacter(); //清空
	void ClearCharacter(const string name); //清除某一角色
	void FinishAction(); //立刻完成播放动画
	bool Finished(AnimeManager& animeManager); //是否播放完成
	CState& State();
private:
	map<string, sf::Vector2f> actions;

	bool bShow; //是否显示
	bool bFinished; //是否全部播放最后一帧
	CState state;
};