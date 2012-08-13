//Written by nashdal13
//系统类，用于封装系统函数，让main函数看起来不会那么长

#include "InitManager.hpp"

InitManager::InitManager(const string filePath)
{
	//读入初始化文件
	string fontName;//字体名称	
	string numInfo; //记录数字信息

	//从初始化文件中读入模式
	ifstream infile(filePath.c_str());
	if(!infile)
	{
		throw runtime_error("Cannot open the initializing file: "+filePath);
	}
	while(!infile.eof())
	{
		//读入指令名称
		string com_name;
		ReadVariable(infile,com_name);

		//判断指令
		if(com_name == "Window_Width")
			ReadVariable(infile,width);
		else if(com_name == "Window_Height")
			ReadVariable(infile,height);
		else if(com_name == "Window_Bits_Per_Pixel")
			ReadVariable(infile,bpp);
		else if(com_name == "Window_Title")
			ReadVariable(infile,windowName);
		else if(com_name == "Window_Flag")
			ReadVariable(infile,windowFlag);
		else if(com_name == "Add_Font")
		{
			string font_name;
			ReadVariable(infile,font_name);
			fontNames.push_back(font_name);
		}
		else if(com_name == "Icon_File")
			ReadVariable(infile,iconName);
		else if(com_name == "Logo_File")
			ReadVariable(infile,logoPicName);
		else if(com_name == "Logo_Background_Color_Red")
		{
			unsigned int r;
			ReadVariable(infile,r);
			color.r = r;
		}
		else if(com_name == "Logo_Background_Color_Green")
		{
			unsigned int g;
			ReadVariable(infile,g);
			color.g = g;
		}
		else if(com_name == "Logo_Background_Color_Blue")
		{
			unsigned int b;
			ReadVariable(infile,b);
			color.b = b;
		}
		else if(com_name == "Logo_Time")
			ReadVariable(infile,logoTime);
		else if(com_name == "Logo_Alpha_Time")
			ReadVariable(infile,logoAlphaTime);
		else if(com_name == "Mouse_File")
			ReadVariable(infile,mousePicName);
		else if(com_name == "Resource_File")
			ReadVariable(infile,resourceFileName);
		else
			throw runtime_error("Cannot identify the command in the initialization file.");

	}

	infile.close();
	infile.clear();
}
