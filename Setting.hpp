//…Ë∂®¿‡
//Written by nashdal13
#include "System.hpp"
#ifndef DIAM
	#define DIAM
	#include "DialogueManager.hpp"
#endif

class SettingManager
{
public:
	SettingManager();
	DState preState;
	bool bInitialized;
	wstring preContent;
	wstring preName;
	unsigned int preNameLength;
	bool showDialogue;
	bool showName;
};