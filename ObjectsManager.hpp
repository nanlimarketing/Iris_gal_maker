//����������ӵĶ���
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
	void AddObject(string name); //���һ������
	void RemoveObject(string name); //�Ƴ�һ������
	void ClearObjects(); //�Ƴ����ж���
	void Draw(AnimeManager& animeManager, sf::RenderWindow& window); //�������ж���
private:
	vector<string> objects;
};