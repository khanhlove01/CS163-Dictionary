#include "Header1.h"
#include "Console.h"
#include "function.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>

//Co dang dich hay khong
bool BTrangThaiDichTu = false;
int dataset = 4;

unordered_map<string, string> mymap;
vector <string> v;
string ss;
string path = "Data/History/list.txt";
ifstream fin;

/*
* Black 0
* Blue 1
* Green 2
* Cyan 3
* Red 4
* Magenta 5
* Yellow 6
* White 7
* Gray 8
* Light Blue 9
* Light Green 10
* Light Cyan 11
* Light Red 12
* Light Magenta 13
* Light Yellow 14
* Bright White 15
*/



void veTieuDeTuDien()
{
	short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
	const char* STRTitle = "Dictionary";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTitle) / 2), 1, 14, 0, STRTitle);
	STRTitle = "Made by Group 11\n";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRTitle) / 2), 2, 14, 0, STRTitle);
	setColor(7);
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
}

void veMenuChinh(short SIndex)
{
	//Cap nhat lai vi tri dang chon va tong muc cua menu
	SViTriChon = SIndex;
	STongMuc = 12;

	//Ve menu
	const char* STRNewGame = "Choose Data Sets";
	setColorBGTextXY(8, MENU_TEXT_ROW, 15, ((SIndex == 0) ? 2 : 0), STRNewGame);
	STRNewGame = "Add a word to favourite list";
	setColorBGTextXY(8, MENU_TEXT_ROW + 1, 15, ((SIndex == 1) ? 2 : 0), STRNewGame);
	STRNewGame = "Search for a definition";
	setColorBGTextXY(8, MENU_TEXT_ROW + 2, 15, ((SIndex == 2) ? 2 : 0), STRNewGame);
	STRNewGame = "View search history";
	setColorBGTextXY(8, MENU_TEXT_ROW + 3, 15, ((SIndex == 3) ? 2 : 0), STRNewGame);
	STRNewGame = "Add a new word";
	setColorBGTextXY(8, MENU_TEXT_ROW + 4, 15, ((SIndex == 4) ? 2 : 0), STRNewGame);
	STRNewGame = "Edit the definition of an existing word";
	setColorBGTextXY(8, MENU_TEXT_ROW + 5, 15, ((SIndex == 5) ? 2 : 0), STRNewGame);
	STRNewGame = "Remove a word from the dictionary";
	setColorBGTextXY(8, MENU_TEXT_ROW + 6, 15, ((SIndex == 6) ? 2 : 0), STRNewGame);
	STRNewGame = "Reset the dictionary";
	setColorBGTextXY(8, MENU_TEXT_ROW + 7, 15, ((SIndex == 7) ? 2 : 0), STRNewGame);
	STRNewGame = "View a random word and its definition";
	setColorBGTextXY(8, MENU_TEXT_ROW + 8, 15, ((SIndex == 8) ? 2 : 0), STRNewGame);
	STRNewGame = "View the favorite list";
	setColorBGTextXY(8, MENU_TEXT_ROW + 9, 15, ((SIndex == 9) ? 2 : 0), STRNewGame);
	STRNewGame = "Remove/Add a word from the favourite list";
	setColorBGTextXY(8, MENU_TEXT_ROW + 10, 15, ((SIndex == 10) ? 2 : 0), STRNewGame);
	STRNewGame = "Exit";
	setColorBGTextXY(8, MENU_TEXT_ROW + 11, 15, ((SIndex == 11) ? 2 : 0), STRNewGame);

}

void veMenuNgonNgu(short SIndex)
{
	//Cap nhat lai vi tri dang chon va tong muc cua menu
	SViTriChon = SIndex;
	STongMuc = 6;

	//Ve menu
	const char* STRNewGame = "English to English";
	setColorBGTextXY(8, MENU_TEXT_ROW, 15, ((SIndex == 0) ? 2 : 0), STRNewGame);
	STRNewGame = "English to Vietnamese";
	setColorBGTextXY(8, MENU_TEXT_ROW + 1, 15, ((SIndex == 1) ? 2 : 0), STRNewGame);
	STRNewGame = "Vietnamese to English";
	setColorBGTextXY(8, MENU_TEXT_ROW + 2, 15, ((SIndex == 2) ? 2 : 0), STRNewGame);
	STRNewGame = "Slang Dictionary";
	setColorBGTextXY(8, MENU_TEXT_ROW + 3, 15, ((SIndex == 3) ? 2 : 0), STRNewGame);
	STRNewGame = "Emotional Dictionary";
	setColorBGTextXY(8, MENU_TEXT_ROW + 4, 15, ((SIndex == 4) ? 2 : 0), STRNewGame);
	STRNewGame = "Return";
	setColorBGTextXY(8, MENU_TEXT_ROW + 5, 15, ((SIndex == 5) ? 2 : 0), STRNewGame);
}

/*Cac loai menu
* 1) Menu chinh
* 2) chon ngon ngu
* 3) Translate
*/




void xuLyPhim(KEY_EVENT_RECORD key)
{
	
	if (key.bKeyDown) // Co nhan phim
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP: // mui ten len
			//std::cout << "Up" << std::endl;
			switch (STrang)
			{
			case 1: //menu chinh
				if (STongMuc == 12)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					veMenuChinh(SViTriChon);
				}
				break;
			case 2: //ngon ngu
				if (STongMuc == 6)
				{
					if (SViTriChon == 0)
						SViTriChon = STongMuc - 1;
					else
						SViTriChon -= 1;
					veMenuNgonNgu(SViTriChon);
				}
				break;
			case 3: //dich
				if (BTrangThaiDichTu)
				{
					//insert translation initializing code here
				}
				break;
			}
			break;
		case VK_DOWN: // mui ten xuong
			//std::cout << "Down" << std::endl;
			switch (STrang)
			{
			case 1: //menu chinh
				if (STongMuc == 12)
				{
					if (SViTriChon == STongMuc - 1)
						SViTriChon = 0;
					else
						SViTriChon += 1;
					veMenuChinh(SViTriChon);
				}
				break;
			case 2: //ngon ngu
				if (STongMuc == 6)
				{
					if (SViTriChon == STongMuc - 1)
						SViTriChon = 0;
					else
						SViTriChon += 1;
					veMenuNgonNgu(SViTriChon);
				}
				break;
			case 3: //dich
				if (BTrangThaiDichTu)
				{
					//insert translation initializing code here
				}
				break;
			}
			break;
		case VK_LEFT: // mui ten trai
			//std::cout << "Left" << std::endl;
			break;
		case VK_RIGHT: // mui ten phai
			//std::cout << "Right" << std::endl;
			break;
		case VK_RETURN: // phim enter
			//std::cout << "Enter" << std::endl;
			switch (STrang)
			{
			case 1: //menu chinh
				switch (SViTriChon)
				{
				case 0:
					STrang = 2;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuNgonNgu(0);
					break;
				case 1:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					function2_create_favouritelist(mymap);
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				case 2:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					function3_search_definition(mymap);
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				case 3:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					fin.open(path, ios::in);
					while (!fin.eof())
					{
						fin >> ss;
						cout << ss << endl;
					}
					fin.close();
					system("pause");
					STrang = 1;
					deleteRow(0, ConsoleHeight);
					veTieuDeTuDien();
					veMenuChinh(0);
					break;
				case 4:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					function5_edit_definition(mymap, v, dataset);
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				case 5:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					function6_edit_definition(mymap, v, dataset);
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				case 6:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					function7_remove(mymap, v, dataset);
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				case 7:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					function8_reset(mymap, dataset, v);
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				case 8:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					function9_viewrandom(mymap, v);
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				case 9:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					function10_viewfavouritelist();
					cout << endl;
					system("pause");
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				case 10:
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				case 11:
					exit(0);
				}
				break;
			case 2: //ngon ngu
				switch (SViTriChon)
				{
				case 0:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					//Them code init dictionary o day
					break;
				case 1:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					//Them code init dictionary o day
					break;
				case 2:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					//Them code init dictionary o day
					break;
				case 3:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					input_data_slang(mymap, fin, v);
					dataset = 4;
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					//break;
				case 4:
					STrang = 3;
					deleteRow(MENU_TEXT_ROW, 12);
					input_data_emotional(mymap, fin, v);
					dataset = 5;
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					//break;
				case 5:
					STrang = 1;
					deleteRow(MENU_TEXT_ROW, 12);
					veMenuChinh(0);
					break;
				}
				break;
			}
		}
	}
}

void xuLySuKien()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0; //Luu lai su kien tai
		DWORD DWNumberOfEventsRead = 0; //Luu lai so luong su kien da duoc loc

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE); //Thiet bi dau vao
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents); // Dat su kien dau vao cua giao dien cho bien DWNumberOfEvents

		if (DWNumberOfEvents)
		{
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents];//Con tro EventBuffer
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead); //Dat cac su kien duoc luu tru vao con tro

			//chay vong lap de doc su kien
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT) //Neu la su kien phim
				{
					xuLyPhim(IREventBuffer[i].Event.KeyEvent);
				}
				//else if (IREventBuffer[i].EventType == MOUSE_EVENT) // Su kien chuot
			}
		}
	}

}

