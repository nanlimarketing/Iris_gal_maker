//Written by nashdal13
//主脚本类，执行游戏的脚本
//First Draft: 2012.4.21

#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif

#ifndef INIT
	#define INIT
	#include "InitManager.hpp"
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
#ifndef ANIMEM
	#define ANIMEM
	#include "AnimeManager.hpp"
#endif
#ifndef SOUNDM
	#define SOUNDM
	#include "SoundManager.hpp"
#endif
#ifndef BUTTONM
	#define BUTTONM
	#include "ButtonManager.hpp"
#endif
#ifndef OBM
	#define OBM
	#include "ObjectsManager.hpp"
#endif

enum SState{SRun,SAuto,SWait,SChoice,SStop};

class ScriptManager
{
public:
	ScriptManager(InitManager& ini,BgManager& bg, DialogueManager& dm, CharacterManager& cm,AnimeManager& aM,sf::Music& b,sf::Music& d,SoundManager& sm,ButtonManager& bm, ObjectsManager& obm); //构造函数
	~ScriptManager(); //析构函数
	void Init(const string scriptName); //从文件初始化主脚本
	void ResetScript(); //返回脚本头部
	void RunScript(); //执行脚本
	void RunNextScript(); //继续执行脚本
	void JumpToScript(wstring mark); //跳转至标记
	void JumpToScript(unsigned int num); //跳转数量
	int GetScriptNum(); //返回已执行的脚本数量
	SState& State(); //脚本状态
	bool& Auto(); //是否自动运行
	bool bDub;
	bool bBgm;
	bool bInitialized;
	wstring bgmName;
	string bgName;
	string gameFirst;
private:
	vector<pair<wstring,wstring>>::iterator curCom; //现在的命令行（的迭代器）
	wstring command; //记录当前指令
	map<wstring,vector<pair<wstring,wstring>>::iterator> markIters; //记录跳转地址
	
	vector<pair<wstring,wstring>> coms; //命令

	sf::Clock clock; //脚本计时器
	float time; //记录时间
	SState state; //脚本状态
	map<wstring,float> vars; //记录脚本变量
	bool bAuto; //是否自动运行

	//一些需要控制的对象
	BgManager& bgManager;
	DialogueManager& dialogueManager;
	CharacterManager& characterManager;
	AnimeManager& animeManager;
	sf::Music& bgm;
	sf::Music& dub;
	SoundManager& soundManager;
	ButtonManager& buttonManager;
	ObjectsManager& objectsManager;
	InitManager& initManager;
};