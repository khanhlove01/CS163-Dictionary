#include "Header1.h"
#include "main.h"
#include "Console.h"
#include "function.h"

// Trang, Vi tri dang chon, Tong muc
short STrang, SViTriChon, STongMuc;

int main()
{
	resizeConsole(ConsoleWidth, ConsoleHeight); // Console size
	SetConsoleTitle(TEXT("Dictionary")); // Dictionary Title
	Cursor(false);
	veTieuDeTuDien();
	veMenuChinh(0);
	STrang = 1;
	xuLySuKien();
	
	
	/*unordered_map<string, string> mymap,mymap10;*/
	

	/*ifstream fin;
	input_data_slang(mymap10, fin);*/
	/*if (mymap10.find("Slag") != mymap10.end())
	{
		cout << mymap10["Slag"];
	}
	else cout << 1; */
	/*cout << endl;*/

	/*input_data_emotional(mymap, fin);*/
	/*if (mymap.find("(-:") != mymap.end())
	{
		cout << mymap["(-:"];
	}
	else cout << 1;*/
	return 0;
}