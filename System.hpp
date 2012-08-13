//标准库
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <map>
#include <locale>
#include <ctime>
#include <utility>
#include <algorithm>
#include <numeric>

//SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//命名空间
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;
using std::string;
using std::map;
using std::vector;
using std::cerr;
using std::runtime_error;
using std::wstring;
using std::wstringstream;
using std::wifstream;
using std::wcout;
using std::locale;
using std::pair;
using std::find;
using std::find_if;
using std::find_first_of;
using std::make_pair;
using std::ofstream;
using std::wofstream;
using std::multimap;
using std::cin;

//字符串转换函数
string WStringToString(wstring wstr);
wstring StringToWString(string str);

//存储函数
void SaveVariable(ofstream&, string);
void SaveVariable(wofstream&, wstring);
void SaveVariable(ofstream&, float);
void SaveVariable(wofstream&, float);
void SaveVariable(ofstream&, unsigned int);
void SaveVariable(wofstream&, unsigned int);
void SaveVariable(ofstream&, int);
void SaveVariable(wofstream&, int);
void SaveVariable(ofstream&, bool);
void SaveVariable(wofstream&, bool);

//读取函数
void ReadVariable(ifstream& file, string& var);
void ReadVariable(wifstream&, wstring&);
void ReadVariable(ifstream&, float&);
void ReadVariable(wifstream&, float&);
void ReadVariable(ifstream&, unsigned int&);
void ReadVariable(wifstream&, unsigned int&);
void ReadVariable(ifstream&, int&);
void ReadVariable(wifstream&, int&);
void ReadVariable(ifstream&, bool&);
void ReadVariable(wifstream&, bool&);

void JumpOneVariable(ifstream&);
void JumpOneVariable(wifstream&);

float ReadFloat(ifstream&, bool);
float ReadFloat(wifstream&, bool);
unsigned int ReadUnsignedInt(ifstream&, bool);
unsigned int ReadUnsignedInt(wifstream&, bool);
string ReadString(ifstream&, bool);
wstring ReadString(wifstream&, bool);
int ReadInt(ifstream&, bool);
int ReadInt(wifstream&, bool);
bool ReadBool(ifstream&, bool);
bool ReadBool(wifstream&, bool);

string GetSecond(); //获取当前秒
string GetTime(); //获取当前时间
string GetDate(); //获取当前日期
