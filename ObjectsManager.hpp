//处理任意添加的动画
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif
#ifndef ANIMEM
	#define ANIMEM
	#include "AnimeManager.hpp"
#endif

class ObjectsManager
{
public:
	void AddObject(string name); //添加一个动画
	void RemoveObject(string name); //移除一个动画
	void ClearObjects(); //移除所有动画
	void Draw(AnimeManager& animeManager, sf::RenderWindow& window); //绘制所有动画
private:
	vector<string> objects;
};