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
		Utils *utils = new Utils();
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
		bool guessWord();
		bool guessMeaning();
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
		cout << "=============== 12. Random a hidden word and guess its meaning " << endl;
		cout << "=============== 13. Guess the correct meaning! " << endl;
		cout << "=============== 14. Exit the program " << endl;
		cout << "===============================================================" << endl;
		cout << "Your option: ";
		cin >> choose;
		if (currentDataset == 0 && choose != 1 && choose != 14) {
			cout << "Please choose a dataset (option 1) first!" << endl;
			console->pause();
		}
		else while (true) {
			console->clear();
			// cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
				case 12: done = guessWord(); break;
				case 13: done = guessMeaning(); break;
				case 14: done = exit(); break;
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
	else if (option == 6) {
		cout << "Operation canceled." << endl;
		return true;
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
	dictionary->showRandom(true);
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

bool Interface::guessWord () {
	string word = dictionary->showRandom(false);
	if (word == "") return true;
	cout << "What word is this? ";
	string guess;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin >> guess;
	cout << "You guessed: " << guess << endl;
	if (word == guess) cout << "That's right!";
	else cout << "That's not the right one :(";
	cout << endl << "The correct word is: " << word << endl;
	return true;
}

bool Interface::guessMeaning () {
	if (dictionary->isEmpty()) {
		dictionary->showRandom(false);
		return true;
	}
	int answer = utils->randInt(3) + 1;
	string guessWord = "";
	cout << "Given 4 definitions: " << endl;
	int answers[4], index = 0;
	answers[index++] = answer;
	for (int i = 1; i <=4; ++i) {
		cout << endl << i << ". ";
		string word = dictionary->showRandom(false);
		if (i == answer) guessWord = word;
		else if (word == guessWord) answers[index++] = i;
	}
	cout << endl << "What is the definition of the word: " << guessWord << " ? (choose one if duplicates) ";
	int choose;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin >> choose;
	bool right = false;
	for (int i = 0; i < index; ++i) {
		if (choose == answers[i]) {
			cout << "That's right!";
			right = true;
			break;
		}
	}
	if (!right) cout << "Wrong answer :(";
	cout << endl << "Answer(s): ";
	for (int i = 0; i < index - 1; ++i) cout << answers[i] << ", ";
	cout << (index > 1 ? "or " : "") << answers[index - 1] << "." << endl;
	return true;
}

bool Interface::exit () {
	if (dictionary != NULL) dictionary->close();
	userExit = true;
	cout << "Thank you for using our dictionary!" << endl;
	return true;
}