#include "Header1.h"

void inter_face()
{
	unordered_map<string, string> mymap;
	vector <string> v;
	int dataset = 0;
	while (1)
	{
		system("cls");
		int choose;
		cout << "===============================================================" << endl;
		cout << "=============== Group 11: Dictionary project ==================" << endl;
		cout << "=============== 1. Choose Data Sets" << endl;
		cout << "=============== 2. Add a word to favourite list" << endl;
		cout << "=============== 3. Users can search for a definition" << endl;
		cout << "=============== 4. View the history" << endl;
		cout << "=============== 5. Add a new word" << endl;
		cout << "=============== 6. Edit the definition of existingh word" << endl;
		cout << "=============== 7. Remove a word from the dictionary" << endl;
		cout << "=============== 8. Reset the dictionary " << endl;
		cout << "=============== 9. View a random word and its definition " << endl;
		cout << "=============== 10. View the favorite list " << endl;
		cout << "=============== 11. Remove/Add a word from the favourite list " << endl;
		cout << "===============================================================" << endl;
		cin >> choose;
		if (choose == 1)
		{
			system("cls");
			cout << "=======================================" << endl;
			cout << "====== Option 1: Eng - Eng Dictionary  " << endl;
			cout << "====== Option 2: Eng - Viet Dictionary " << endl;
			cout << "====== Option 3: Viet - Anh Dictionary " << endl;
			cout << "====== Option 4: Slang Dictionary" << endl;
			cout << "====== Option 5: Emotional Dictionary" << endl;
			cout << "Input your option: ";
			int option;
			cin >> option;
			cout << "Input successfully!!!";
			dataset = option;
			ifstream fin;
			if (option == 4)
			{
				input_data_slang(mymap, fin,v);
			}
			else if(option == 5)
			{
				input_data_emotional(mymap, fin,v);
			}
			system("pause");
		}
		if (choose == 2)
		{
			function2_create_favouritelist(mymap);
		}
		if (choose == 3)
		{
			function3_search_definition(mymap);
		}
		if (choose == 4)
		{
			string ss;
			string path = "Data/History/list.txt";
			ifstream fin;
			fin.open(path, ios::in);
			while (!fin.eof())
			{
				fin >> ss;
				cout << ss << endl;
			}
			fin.close();
			system("pause");
		}
		if (choose == 5)
		{
			function5_edit_definition(mymap,v,dataset);
			system("pause");
		}
		if (choose == 6)
		{
			function6_edit_definition(mymap,v,dataset);
			system("pause");
		}
		if (choose == 7)
		{
			function7_remove(mymap,v,dataset);
			system("pause");
		}
		if (choose == 8)
		{
			function8_reset(mymap,dataset,v);
		}
		if (choose == 9)
		{
			function9_viewrandom(mymap, v);
		}
		if (choose == 10)
		{
			function10_viewfavouritelist();
			system("pause");
		}
	}
}