#include <iostream>
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include <fstream>
#include <comdef.h>
#include <windows.h>
using namespace std;
using namespace filesystem;
wstring descript;
map<wstring, wstring> objectList;
const char *mdPath = "readme.md";
fstream fp;
int fsize;
vector<wstring> line;
#define Sname it->first
#define Sdescript it->second

// Windows

// -------方式一---------
std::string Wstring2String(std::wstring wstr)
{
    // support chinese
    std::string res;
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), nullptr, 0, nullptr, nullptr);
    if (len <= 0){
        return res;
    }
    char* buffer = new char[len + 1];
    if (buffer == nullptr){
        return res;
    }
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, nullptr, nullptr);
    buffer[len] = '\0';
    res.append(buffer);
    delete[] buffer;
    return res;
}

std::wstring String2Wstring(std::string wstr)
{
    std::wstring res;
    int len = MultiByteToWideChar(CP_ACP, 0, wstr.c_str(), wstr.size(), nullptr, 0);
    if( len < 0 ){
        return res;
    }
    wchar_t* buffer = new wchar_t[len + 1];
    if( buffer == nullptr){
        return res;
    }
    MultiByteToWideChar(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len);
    buffer[len] = '\0';
    res.append(buffer);
    delete[] buffer;
    return res;
}
int main()
{
	system("chcp 65001");
	system("cls");
	fsize = file_size(mdPath);
	fp = fstream{mdPath, ios::in};
	if (exists(mdPath))
	{
		for (wstring t; getline(fp, t);)
		{
			line.push_back(t);
		}
		for (int i = 0; i < line.size(); i++)
		{
			wstring name, descript;
			int pos = line[i].find(" |");
			descript = line[i].substr(0, pos);
			name = line[i].substr(pos + 3, line[i].size() - pos - 5);
			objectList[name] = descript;
		}
	}
	fp.close();

	directory_iterator list(current_path());
	wcout << "------------------------\n";
	for (auto &it : list)
	{
		wstring fileName = String2Wstring(it.path().filename().string());
		auto pos = fileName.find('.');
		if (pos != fileName.npos)
		{
			fileName.erase(fileName.begin() + pos, fileName.end());
		}
		if (pos == 0)
			continue;
		if (objectList[fileName] == L"")
		{
			wcout << "no descript,add one:";
			wcout << "→" << fileName << ":";
			wcin >> descript;
			objectList[fileName] = descript;
		}
		else
		{
			wcout << objectList[fileName] << " | " << fileName << endl
				 << "descript exist,rewrite?[y,n]";
			wchar_t selection;
			wcin >> selection;
			switch (selection)
			{
			case 'Y':
			case 'y':
				wcout << ">";
				wcin >> descript;
				objectList[fileName] = descript;
				break;
			case 'N':
			case 'n':
				break;
			default:
				wcout << "invalid input,break";
				break;
			}
		}
	}
	wcout << "------------------------\n";
	fp.open(mdPath, ios::out | ios::trunc);
	fp.close();
	fp.open(mdPath, ios::out | ios::app);
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		fp << (it->second + " | " + it->first + "  \n").c_str();
	}
	fp.close();

	return 0;
}