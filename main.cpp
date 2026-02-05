#include <iostream>
#include <string>
#include <filesystem>
#include <stdio.h>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
using namespace filesystem;
string descript;
map<string, string> objectList;
const char *mdPath = "readme.md";
fstream fp;
int fsize;
vector<string> line;
#define Sname it->first
#define Sdescript it->second
int main()
{
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
			name = line[i].substr(0, pos);
			descript = line[i].substr(pos + 3, line[i].size() - pos - 2);
			objectList[name] = descript;
		}
	}
	fp.close();
	for(auto it=objectList.begin();it!=objectList.end();it++){
		cout<<Sname<<"|"<<Sdescript<<endl;
	}

	directory_iterator list(current_path());
	cout << "------------------------\n";
	for (auto &it : list)
	{
		string fileName = it.path().filename().string();
		auto pos = fileName.find('.');
		if (pos != fileName.npos)
		{
			// cout<<pos;
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
			cout << "descripted:" << objectList[fileName] << "input if want to redescript,else enter:" << endl;
		}
	}
	cout << "------------------------\n";
	fp.open(mdPath, ios::out | ios::trunc);
	fp.close();
	fp.open(mdPath, ios::out | ios::app);
	for (auto it = objectList.begin(); it != objectList.end(); it++)
	{
		cout << it->second << " | " << it->first << endl;
		fp << (it->second + " | " + it->first + "  \n").c_str();
	}
	fp.close();

	return 0;
}