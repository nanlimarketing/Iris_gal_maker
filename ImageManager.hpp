//Written by nashdal13
//图片类，用于存储和管理图像资源
//First Draft: 2012.3.26
//2012.3.27 Revised: 增加析构函数
//2012.4.4 Revised: 增加读入单个图像的接口，修改private数据结构
//2012.4.4 Revised: 增加清除接口
#ifndef SYSTEM
	#define SYSTEM
	#include "System.hpp"
#endif

class ImageManager
{
public:
	ImageManager(); //构造函数，其实是空的^_^
	~ImageManager(); //析构函数，清空所有图像
	void LoadImages(const vector<string> names); //从文件名数组读取一系列图像
	void LoadImage(const string name); //从文件名读取一个图像
	void CreateImage(const string name, const unsigned int width, const unsigned int Height, sf::Color color);
	sf::Image& GetImage(const string name); //返回给定文件名的图像
	sf::Image& operator[] (const string name); //用下标获得图像
	void ClearImages(); //清空所有图像
	void ClearImages(const vector<string> names); //清空一系列图像
	void ClearImage(const string name); //清空某一个图像
private:
	map<string,sf::Image> images; //图像数组
};
