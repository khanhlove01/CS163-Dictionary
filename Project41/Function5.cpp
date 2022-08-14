#include "Header1.h"
#include "Console.h"
#include "function.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>


void function5_edit_definition(unordered_map<string, string>& mymap10, vector<string>& v,int dataset)
{
	string str, str1;
	const char* STRTitle = "Input word and definition you want to add: ";
	setColorBGTextXY(8, MENU_TEXT_ROW, 15, 0, STRTitle);
	STRTitle = "Input word: ";
	setColorBGTextXY(8, MENU_TEXT_ROW+1, 15, 0, STRTitle);
	cin.ignore();
	getline(cin, str);
	STRTitle = "Input definition: ";
	setColorBGTextXY(8, MENU_TEXT_ROW + 2, 15, 0, STRTitle);
	//cin.ignore();
	getline(cin, str1);
	mymap10[str] = str1;
	if (dataset == 4)
	{
		ofstream fout;
		string path = "Data/slang.txt";
		fout.open(path, ios::app);
		fout << str << endl << str1 << endl;
		fout.close();
	}
	if (dataset == 5)
	{
		ofstream fout;
		string path = "Data/emotional.txt";
		fout.open(path, ios::app);
		fout << str << endl << str1 << endl;
		fout.close();
	}
}