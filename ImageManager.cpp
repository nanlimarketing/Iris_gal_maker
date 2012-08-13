//Written by nashdal13
//图片类，用于存储和管理图像资源
#include "ImageManager.hpp"

ImageManager::ImageManager()
{
	
}

ImageManager::~ImageManager()
{
	ClearImages();
}

void ImageManager::LoadImages(const vector<string> names)
{
	//从文件名中读入图像
	for(vector<string>::const_iterator iter = names.begin(); iter != names.end(); iter++)
	{
		if(*iter != "NONE")
		{
			sf::Image img;
			if(!img.LoadFromFile(iter->c_str()))
				throw runtime_error("Cannot load the image: "+*iter);
			//img.CreateMaskFromColor(sf::Color::Black);
			images[*iter] = img;
		}
	}
}

void ImageManager::LoadImage(const string name)
{
	if(name != "NONE")
	{
		//从文件名中读入图像
		sf::Image img;
		if(!img.LoadFromFile(name.c_str()))
			throw runtime_error("Cannot load the image: "+name);
		//img.CreateMaskFromColor(sf::Color::Black);
		images[name] = img;
	}
}

void ImageManager::CreateImage(const string name, const unsigned int width, const unsigned int height, sf::Color color)
{
	sf::Image img(width,height,color);
	images[name] = img;
}

sf::Image& ImageManager::GetImage(const string name)
{
	//返回指定文件名的图像
	if(images.count(name))
	{
		return images[name];
	}
	else
		throw runtime_error("Cannot find the image: "+name);
}

sf::Image& ImageManager::operator[](const string name)
{
	if(images.count(name))
	{
		return images[name];
	}
	else
		throw runtime_error("Cannot find the image: "+name);
}

void ImageManager::ClearImages()
{
	//清空现有图像
	images.clear();
}

void ImageManager::ClearImages(const vector<string> names)
{
	for(vector<string>::const_iterator iter = names.begin();iter != names.end();iter++)
	{
		images.erase(*iter);
	}
}

void ImageManager::ClearImage(const string name)
{
	//清空某图像
	images.erase(name);
}
