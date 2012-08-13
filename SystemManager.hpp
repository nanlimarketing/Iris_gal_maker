//Written by nashdal13
//系统类，用于封装系统对象，并负责初始化系统对象
//包括初始化鼠标，初始化主界面
//First Draft: 2012.4.3
//2012.4.4 Revised: 昨天没写完
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif

#ifndef WINDOW
	#define WINDOW
	#include "WindowManager.hpp"
#endif
#ifndef FONT
	#define FONT
	#include "FontManager.hpp"
#endif
#ifndef TEXT
	#define TEXT
	#include "Text.hpp"
#endif
#ifndef INPUT
	#define INPUT
	#include "InputManager.hpp"
#endif
#ifndef IMAGE
	#define IMAGE
	#include "ImageManager.hpp"
#endif
#ifndef ANIMEM
	#define ANIMEM
	#include "AnimeManager.hpp"
#endif
#ifndef ANIME
	#define ANIME
	#include "Anime.hpp"
#endif
#ifndef INIT
	#define INIT
	#include "InitManager.hpp"
#endif
#ifndef SCRIPT
	#define SCRIPT
	#include "ScriptManager.hpp"
#endif
#ifndef DIAM
	#define DIAM
	#include "DialogueManager.hpp"
#endif
#ifndef CHAM
	#define CHAM
	#include "CharacterManager.hpp"
#endif
#ifndef SOUNDM
	#define SOUNDM
	#include "SoundManager.hpp"
#endif
#ifndef BUTTONM
	#define BUTTONM
	#include "ButtonManager.hpp"
#endif
#ifndef FILEM
	#define FILEM
	#include "FileManager.hpp"
#endif

enum State{Init,Main,Game,Save,Load,Setting,Transit,Exit}; //游戏状态

class SystemManager: private sf::Thread
{
public:
	SystemManager(InitManager& initM, ImageManager& imageM, AnimeManager& animeM, FontManager& fontM, InputManager& inputM, 
		DialogueManager& dialogueM, CharacterManager& characterM, SoundManager& soundM, ButtonManager& buttonM, FileManager& fileM, ScriptManager& scriptM);
	void Logo(); //载入初始图标
	void DrawLogo(sf::RenderWindow& window); //绘制LOGO
	void Initialize(); //读入所有资源
	State& GameState(); //获取游戏状态
	string SystemFont(); //返回系统字体名称
	string mainBg; //主菜单背景
	string setBg; //设定背景
	string saveBg,loadBg; //存取背景
	string exit; //推出提示
	string sounds,dialogue,text; //设定图片

	string preBg; //记录之前的背景
	State preState; //记录之前的游戏状态
	State exitState; //记录推出前的游戏状态

	float bgmVolume; //记录游戏的音量
	float dubVolume; //记录游戏配音的音量
	Text bgmVol;
	Text dubVol;
	Text sfxVol;
	Text red,green,blue,alpha;
	Text tRed,tGreen,tBlue;

	sf::Image screenImage; //记录屏幕用
	float pos_x,pos_y;
	float scale;
private:
	virtual void Run();
	
	void CreateButton(ifstream&, wstring);
	void CreateAnime(ifstream&);
	void CreateFileButton(ifstream&,float,float,float);

	//操作的系统对象
	InitManager& initManager;
	AnimeManager& animeManager;
	FontManager& fontManager;
	InputManager& inputManager;
	ImageManager& imageManager;
	ScriptManager& scriptManager;
	DialogueManager& dialogueManager;
	CharacterManager& characterManager;
	SoundManager& soundManager;
	ButtonManager& buttonManager;
	FileManager& fileManager;

	State gameState; //记录游戏处于什么状态
	sf::Clock clock; //系统计时器
	bool bInitialized; //是否已经初始化完成
	string sysFont; //系统字体名称
};