
	//------------------------------------------------------

	// directory_iterator list(current_path());
	// cout << "------------------------\n";
	// for (auto &it : list)
	// {
	// 	string fileName = it.path().filename().string();
	// 	auto pos = fileName.find('.');
	// 	if (pos != fileName.npos)
	// 	{
	// 		fileName.erase(fileName.begin() + pos, fileName.end());
	// 	}
	// 	if (pos == 0)
	// 		continue;
	// 	if (objectList[fileName] == "")
	// 	{
	// 		cout << "no descript,add one:";
	// 		cout << "→" << fileName << ":";
	// 		cin >> descript;
	// 		objectList[fileName] = descript;
	// 	}
	// 	else
	// 	{
	// 		cout << objectList[fileName] << " | " << fileName << endl
	// 			 << "descript exist,rewrite?[y,n]";
	// 		char selection;
	// 		cin >> selection;
	// 		switch (selection)
	// 		{
	// 		case 'Y':
	// 		case 'y':
	// 			cout << ">";
	// 			cin >> descript;
	// 			objectList[fileName] = descript;
	// 			break;
	// 		case 'N':
	// 		case 'n':
	// 			break;
	// 		default:
	// 			cout << "invalid input,break";
	// 			break;
	// 		}
	// 	}
	// }
	// cout << "------------------------\n";
