#include "structure.h"
#include "console.h"
#include <cstring>

class Interface {
	public:
		void run ();
	private:
		bool userExit = false;
		Dictionary *dictionary = NULL;
		int currentDataset = 0;
		ConsoleOperation *console = new ConsoleOperation();
		bool chooseDataSet();
		bool addFavorite();
		bool findWord();
		bool viewHistory();
		bool addWord();
		bool editWord();
		bool removeWord();
		bool reset();
		bool randomWord();
		bool viewFavorite();
		bool removeFavorite();
		bool exit();
		bool prompt(string message);
};

void Interface::run ()
{
	while (true)
	{
		console->clear();
		int choose;
		cout << "===============================================================" << endl;
		cout << "=============== Group 11: Dictionary project ==================" << endl;
		cout << "=============== 1. Choose Data Sets" << endl;
		cout << "=============== 2. Add a word to favourite list" << endl;
		cout << "=============== 3. Search the word for definition" << endl;
		cout << "=============== 4. View the history" << endl;
		cout << "=============== 5. Add a new word" << endl;
		cout << "=============== 6. Edit the definition of existing custom word" << endl;
		cout << "=============== 7. Remove a word from the dictionary" << endl;
		cout << "=============== 8. Reset the dictionary " << endl;
		cout << "=============== 9. View a random word and its definition " << endl;
		cout << "=============== 10. View the favorite list " << endl;
		cout << "=============== 11. Remove a word from the favourite list " << endl;
		cout << "=============== 12. Exit the program " << endl;
		cout << "===============================================================" << endl;
		cout << "Your option: ";
		cin >> choose;
		if (currentDataset == 0 && choose != 1 && choose != 12) {
			cout << "Please choose a dataset (option 1) first!" << endl;
			console->pause();
		}
		else while (true) {
			console->clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			bool done = false;
			switch (choose) {
				case 1: done = chooseDataSet(); break;
				case 2: done = addFavorite(); break;
				case 3: done = findWord(); break;
				case 4: done = viewHistory(); break;
				case 5: done = addWord(); break;
				case 6: done = editWord(); break;
				case 7: done = removeWord(); break;
				case 8: done = reset(); break;
				case 9: done = randomWord(); break;
				case 10: done = viewFavorite(); break;
				case 11: done = removeFavorite(); break;
				case 12: done = exit(); break;
			}
			console->pause();
			if (userExit) return;
			if (done) break;
		}
	}
}

bool Interface::prompt (string message) {
	char prompt;
	cout << message << " (Y/N): ";
	cin >> prompt;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return tolower(prompt) == 'y';
}

bool Interface::chooseDataSet () {
	cout << "=======================================" << endl;
	cout << "====== Option 1: English - English" << endl;
	cout << "====== Option 2: English - Vietnamese" << endl;
	cout << "====== Option 3: Vietnamese - English" << endl;
	cout << "====== Option 4: Slang" << endl;
	cout << "====== Option 5: Emotional" << endl;
	cout << "====== Option 6: Go back" << endl;
	cout << "Input your option: ";
	int option;
	cin >> option;;
	if (option < 1 || option > 6) {
		cout << "Invalid choice!" << endl;
		return false;
	}
	else if (option == currentDataset) {
		cout << "You are already in this dataset!" << endl;
		return false;
	}
	else {
		currentDataset = option;
		string name, path;
		switch (option) {
			case 1: name = "English - English"; path = "en-en"; break;
			case 2: name = "English - Vietnamese"; path = "en-vi"; break;
			case 3: name = "Vietnamese - English"; path = "vi-en"; break;
			case 4: name = "Slang"; path = "slang"; break;
			case 5: name = "Emotional"; path = "emotional"; break;
			case 6: cout << "Operation canceled." << endl; return true;
		}

		if (dictionary != NULL) dictionary->close();
		dictionary = new Dictionary(name, path);
		dictionary->load();

		cout << "Switched Dataset successfully!" << endl;

		return true;
	}
}

bool Interface::addFavorite () {
	string word;
	cout << "Enter the word you want to add to the favorite list: ";
	cin >> word;
	if (!dictionary->wordExists(word)) {
		cout << "Word does not exist!" << endl;
		return true;
	}
	if (!dictionary->favorites->add(word)) {
		cout << "The word already exists in your list!" << endl;
		return true;
	}
	cout << "Added the word to your favorites list!" << endl;
	return true;
}

bool Interface::findWord () {
	cout << "Enter the one you want to lookup: ";
	string word;
	cin >> word;
	dictionary->display(word);
	return true;
}

bool Interface::viewHistory () {
	cout << "Loookup history:" << endl;
	dictionary->history->display(cout);
	if (dictionary->history->isEmpty()) cout << "No recent history!" << endl;
	return true;
}

bool Interface::addWord () {
	cout << "Enter the new word you want to add: ";
	string word;
	cin >> word;
	if (dictionary->wordExists(word)) {
		cout << "Word already exists!" << endl;
		return true;
	}
	cout << "Type the definition: ";
	string definition;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, definition);
	dictionary->add(word, definition, true);
	cout << "Your new word has been added." << endl;
	return true;
}

bool Interface::editWord () {
	cout << "Enter the word you want to edit: ";
	string word;
	cin >> word;
	Character *res = dictionary->find(word);
	if (res == NULL) {
		cout << "Word doesn't exist" << endl;
		return true;
	}
	if (!res->isCustom) {
		cout << "You don't have permissions to edit non-custom words." << endl;
		return true;
	}
	cout << "Type the new definition: ";
	string definition;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, definition);
	res->definition.clear();
	res->definition.push_back(definition);
	cout << "Your changes have been applied." << endl;
	return true;
}

bool Interface::removeWord () {
	cout << "Enter the word you want to remove: ";
	string word;
	cin >> word;
	Character *res = dictionary->find(word);
	if (res == NULL) {
		cout << "Word doesn't exist" << endl;
		return true;
	}
	if (!res->isCustom) {
		cout << "You don't have permissions to remove non-custom words." << endl;
		return true;
	}
	dictionary->remove(word);
	cout << "The word has been removed." << endl;
	return true;
}

bool Interface::reset () {
	if (prompt("Are you sure to clear all your custom words?")) {
		dictionary->reset();
		cout << "All custom words have been removed." << endl;
	}
	else cout << "Operation canceled." << endl;
	return true;
}

bool Interface::randomWord () {
	if (dictionary->isEmpty()) cout << "No words to random!" << endl;
	else dictionary->random();
	return true;
}

bool Interface::viewFavorite () {
	cout << "Favorite words list:" << endl;
	dictionary->favorites->display(cout);
	if (dictionary->favorites->isEmpty()) cout << "No favorite words!" << endl;
	return true;
}

bool Interface::removeFavorite () {
	cout << "Enter the word you want to remove from favorite: ";
	string word;
	cin >> word;
	if (!dictionary->favorites->remove(word)) cout << "Word doesn't exist in favorite list!" << endl;
	else cout << "The word has been removed." << endl;
	return true;
}

bool Interface::exit () {
	if (dictionary != NULL) dictionary->close();
	userExit = true;
	cout << "Thank you for using our dictionary!" << endl;
	return true;
}