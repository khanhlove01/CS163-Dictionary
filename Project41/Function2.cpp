#include "Header1.h"
#include "Console.h"
#include "function.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>

void function2_create_favouritelist(unordered_map<string, string>& mymap10)
{
	string path = "Data/Favourite_list";
	/*_mkdir(path.c_str());*/
	ofstream fout;
	path = "Data/Favourite_list/list.txt";
	fout.open(path, ios::app);
	const char* STRTitle = "Input word: ";
	setColorBGTextXY(8, MENU_TEXT_ROW + 1, 15, 0, STRTitle);
	string str;
	cin >> str;
	if (mymap10.find(str) != mymap10.end())
	{
		//fout << str << endl;
		//fout << str << endl;
		fout << str << endl;
		STRTitle = "Add successfully !!!\n";
		setColorBGTextXY(8, MENU_TEXT_ROW + 2, 15, 0, STRTitle);
		system("pause");
	}
	else
	{
		STRTitle = "Can't find the word you need !!!\n";
		setColorBGTextXY(8, MENU_TEXT_ROW + 2, 15, 0, STRTitle);
		system("pause");
	}
	fout.close();
}