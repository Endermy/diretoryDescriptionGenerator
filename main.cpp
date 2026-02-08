#define _STDCALL_SUPPORTED

#include <iostream>
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include <fstream>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
using namespace ImGui;
using namespace std;
using namespace filesystem;

string descript;
// wstring descript;
map<string, string> objectList;
const char *mdPath = "readme.md";
fstream fp;
int fsize;
vector<string> line;
#define Sname it->first
#define Sdescript it->second

int main()
{
	system("chcp 65001");
	system("cls");
	fsize = file_size(mdPath);
	fp = fstream{mdPath, ios::in};
	if (exists(mdPath))
	{
		for (string t; getline(fp, t);)
		{
			line.push_back(t);
		}
		for (int i = 0; i < line.size(); i++)
		{
			string name, descript;
			int pos = line[i].find(" |");
			descript = line[i].substr(0, pos);
			name = line[i].substr(pos + 3, line[i].size() - pos - 5);
			objectList[name] = descript;
		}
	}
	fp.close();

	directory_iterator list(current_path());
	cout << "------------------------\n";
	for (auto &it : list)
	{
		string fileName = it.path().filename().string();
		auto pos = fileName.find('.');
		if (pos != fileName.npos)
		{
			fileName.erase(fileName.begin() + pos, fileName.end());
		}
		if (pos == 0)
			continue;
		if (objectList[fileName] == "")
		{
			cout << "no descript,add one:";
			cout << "→" << fileName << ":";
			cin >> descript;
			objectList[fileName] = descript;
		}
		else
		{
			cout << objectList[fileName] << " | " << fileName << endl
				 << "descript exist,rewrite?[y,n]";
			char selection;
			cin >> selection;
			switch (selection)
			{
			case 'Y':
			case 'y':
				cout << ">";
				cin >> descript;
				objectList[fileName] = descript;
				break;
			case 'N':
			case 'n':
				break;
			default:
				cout << "invalid input,break";
				break;
			}
		}
	}
	cout << "------------------------\n";
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