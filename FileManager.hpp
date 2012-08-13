#ifndef DIAM
	#define DIAM
	#include "DialogueManager.hpp"
#endif

class FileManager
{
public:
	FileManager();
	~FileManager();

	void AddFileButton(const wstring info, const string picN, const string coverN, const string coverCN, const string clickedN, const float pX, const float pY, const float cX, const float cY, 
	unsigned int a, const float bX, const float bY,const unsigned int bW, const unsigned int bH);
	void SetText(wstring, float, float, wstring);
	void SetTextSize(float s);

	wstring GetFileButtonText(const wstring);
	Choice& GetFileButton(const wstring);

	wstring UpdateFileButtons(const float, const float);
	void DrawFileButtons(AnimeManager& animeManager, sf::Font& font, sf::RenderWindow& window);
private:
	vector<Choice> fileButtons;
	float size;
	sf::Color color;
};