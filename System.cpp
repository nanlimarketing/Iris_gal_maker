#include "System.hpp"
#define WIN
string WStringToString(wstring wstr)
{
	//��������Locale������Ϊ936
#ifdef WIN
	setlocale(LC_ALL, ".936"); 
#endif
#ifdef LINUX
	setlocale(LC_ALL, "zh_CN.gbk"); 
#endif
	const wchar_t* _Source = wstr.c_str();
	size_t _Dsize = 2 * wstr.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	string result = _Dest;
	delete []_Dest;
	//�ָ�Ĭ��Locale
	setlocale(LC_ALL, NULL);
	//���ؽ��
	return result;
}

wstring StringToWString(string str)
{
#ifdef WIN
	setlocale(LC_ALL, ".936"); 
#endif
#ifdef LINUX
	setlocale(LC_ALL, "zh_CN.gbk"); 
#endif
	const char* _Source = str.c_str();
	size_t _Dsize = str.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL,NULL);
	return result;
}

void SaveVariable(ofstream& file, float var)
{
	file<<var<<" ";
}

void SaveVariable(wofstream& file, float var)
{
	file<<var<<" ";
}

void SaveVariable(ofstream& file, bool var)
{
	file<<var<<" ";
}

void SaveVariable(wofstream& file, bool var)
{
	file<<var<<" ";
}

void SaveVariable(ofstream& file, string var)
{
	file<<var<<" ";
}

void SaveVariable(ofstream& file, unsigned int var)
{
	file<<var<<" ";
}

void SaveVariable(wofstream& file, unsigned int var)
{
	file<<var<<" ";
}

void SaveVariable(ofstream& file, int var)
{
	file<<var<<" ";
}

void SaveVariable(wofstream& file, int var)
{
	file<<var<<" ";
}

void SaveVariable(wofstream& file, wstring var)
{
	file<<var<<" ";
}

//�ļ���ȡ����
void ReadVariable(ifstream& file, string& var)
{
	file>>var;
}

void ReadVariable(wifstream& file, wstring& var)
{
	file>>var;
}

void ReadVariable(ifstream& file, float& var)
{
	file>>var;
}

void ReadVariable(wifstream& file, float& var)
{
	file>>var;
}

void ReadVariable(ifstream& file, unsigned int& var)
{
	file>>var;
}

void ReadVariable(wifstream& file, unsigned int& var)
{
	file>>var;
}

void ReadVariable(ifstream& file, int& var)
{
	file>>var;
}

void ReadVariable(wifstream& file, int& var)
{
	file>>var;
}

void ReadVariable(ifstream& file, bool& var)
{
	file>>var;
}

void ReadVariable(wifstream& file, bool& var)
{
	file>>var;
}

//��������

void JumpOneVariable(ifstream& file)
{
	string temp;
	file>>temp;
}
void JumpOneVariable(wifstream& file)
{
	wstring temp;
	file>>temp;
}

//���ض�ȡ����
float ReadFloat(ifstream& file,bool bName = false)
{
	if(bName)
	{
		string jump;
		file >> jump;
	}
	float temp;
	file>>temp;
	return temp;
}

float ReadFloat(wifstream& file,bool bName = false)
{
	if(bName)
	{
		wstring jump;
		file >> jump;
	}
	float temp;
	file>>temp;
	return temp;
}

unsigned int ReadUnsignedInt(ifstream& file, bool bName = false)
{
	if(bName)
	{
		string jump;
		file >> jump;
	}
	unsigned int temp;
	file>>temp;
	return temp;
}

unsigned int ReadUnsignedInt(wifstream& file, bool bName = false)
{
	if(bName)
	{
		wstring jump;
		file >> jump;
	}
	unsigned int temp;
	file>>temp;
	return temp;
}

string ReadString(ifstream& file, bool bName = false)
{
	if(bName)
	{
		string jump;
		file >> jump;
	}
	string temp;
	file>>temp;
	return temp;
}

wstring ReadString(wifstream& file, bool bName = false)
{
	if(bName)
	{
		wstring jump;
		file >> jump;
	}
	wstring temp;
	file>>temp;
	return temp;
}

int ReadInt(ifstream& file, bool bName = false)
{
	if(bName)
	{
		string jump;
		file >> jump;
	}
	int temp;
	file>>temp;
	return temp;
}

int ReadInt(wifstream& file, bool bName = false)
{
	if(bName)
	{
		wstring jump;
		file >> jump;
	}
	int temp;
	file>>temp;
	return temp;
}

bool ReadBool(ifstream& file, bool bName = false)
{
	if(bName)
	{
		string jump;
		file >> jump;
	}
	bool temp;
	file>>temp;
	return temp;
}

bool ReadBool(wifstream& file, bool bName = false)
{
	if(bName)
	{
		wstring jump;
		file >> jump;
	}
	bool temp;
	file>>temp;
	return temp;
}

string GetTime()
{
	char tempBuf[128];
	_strtime(tempBuf);
	string time(tempBuf);
	time.assign(time.begin(),time.begin()+5);
	return time;
}

string GetSecond()
{
	char tempBuf[128];
	_strtime(tempBuf);
	string time(tempBuf);
	time.assign(time.begin()+6,time.begin()+8);
	return time;
}

string GetDate()
{
	char tempBuf[128];
	_strdate(tempBuf);
	string time(tempBuf);
	return time;
}