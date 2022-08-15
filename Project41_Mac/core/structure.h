#include <iostream>
#include <fstream>
#include <vector>
#include "wordcollection.h"
#include "utils.h"

using namespace std;

class Character;

class Charset {
    public:
        char key;
        Character *data;
        Charset *left, *right;
        int height = 1;
        Charset(char k, Character* value): key(k), data(value), left(NULL), right(NULL), height(1) {}

        // ~Charset ();
};

class CharsetTree {
    public:
        Charset *data = NULL;
        Charset* add (char key, Character* &value);
        Charset* find (char key);
        vector<char> toArray();

        void remove (char key);

        bool isEmpty();

        // ~CharsetTree ();
    private:
        Charset *leftRotate(Charset *node);
        Charset *rightRotate(Charset* node);
        Charset* exclude (Charset* &node, char key);
        Charset *insert (Charset *node, char key, Character* &value);
        int getBalance(Charset *node);
        int height(Charset* node);
        void recursiveArray (vector<char> &arr, Charset *data);
};

class Character {
    public:
        Character *parent;
        CharsetTree* nextCharacters = new CharsetTree();
        bool isLastCharacter, isCustom;
        string word;
        vector <string> definition;
        Character () {};
        Character (Character *parent, string def, string kotoba, bool custom): parent(parent), word(kotoba), isLastCharacter(true), isCustom(custom) {
            definition.push_back(def);
        };
        Character (Character *parent): parent(parent), isLastCharacter(false) {};

        void display ();

        Character* next (char f);

        // ~Character ();
};

class Dictionary {
    public:
        string name = "";

        Character *add (string word, string definition, bool isCustom) {
            Character *node = data;
            int len = word.length();
            for (int i = 0; i < len; ++i) {
                int key = word[i];
                Character* nextChar;
                if (i < len - 1) nextChar = new Character(node);
                else nextChar = new Character(node, definition, word, isCustom);
                node = node->nextCharacters->add(key, nextChar)->data;
            }
            node->isLastCharacter = true;
            if (isCustom) custom.push_back(word);
            return node;
        }

        void remove(string word) {
            Character *node = data;
            for (int i = 0; i < word.length(); ++i) {
                node = node->next(word[i]);
                if (node == NULL) return;
            }
            if (!node->isLastCharacter) return;
            // traverse back
            bool lastWordDeleted = false;
            while (node->parent != NULL) {
                Character* cur = node;
                node = node->parent;
                if (!lastWordDeleted) {
                    lastWordDeleted = true;
                    cur->isLastCharacter = false;
                }
                if (cur->isLastCharacter || !cur->nextCharacters->isEmpty()) return;
                node->nextCharacters->remove(word[word.length() - 1]);
            }
        }

        Character* find(string word) {
            Character *node = data;
            for (int i = 0; i < word.length(); ++i) {
                node = node->next(word[i]);
                if (node == NULL) return NULL;
            }
            if (!node->isLastCharacter) return NULL;
            return node;
        }

        bool wordExists (string word) {
            return find(word) != NULL;
        }

        void display (string word) {
            Character *result = find(word);
            if (result == NULL) cout << "No results found for the word '" << word << "'. Maybe you wish to add it as a custom word?" << endl;
            else show(result);
        }

        bool import (string pathToFile, char discriminator, bool repeatable, bool ignoreFirstLine, bool isCustom) {
            ifstream fin(pathToFile);
            if (fin.fail()) {
                fin.close();
                return false;
            }
            Character *wordData;
            while (!fin.eof()) {
                string str, word = "", definition = "";
                int i = 0;
                getline(fin, str);
                if (str == "") continue;
                if (ignoreFirstLine) {
                    ignoreFirstLine = false;
                    continue;
                }
                bool reac = false;
                for (; i < str.length(); ++i) {
                    if (str[i] == discriminator) {
                        reac = true;
                        ++i;
                        if (repeatable) while (str[i] == discriminator) ++i;
                        break;
                    }
                    definition += str[i];
                }
                if (!reac) {
                    if (wordData != NULL) wordData->definition.push_back(definition);
                }
                else {
                    word = definition;
                    definition = "";
                    for (; i < str.length(); ++i) definition += str[i];
                    if (word != "") wordData = add(word, definition, isCustom);
                }
            }
                
            fin.close();

            return true;
        }

        void load () {
            ifstream fin(path + "/config.txt");
            string failed = "Failed to import data for '" + name + "': ";
            if (fin.fail()) return void (cout << failed << "No available configuration files found." << endl);
            string separator;
            bool repeatable, ignoreFirstLine;
            getline(fin, separator);
            if (separator == "TAB") separator = "\t";
            fin >> repeatable >> ignoreFirstLine;
            fin.close();
            if (!import(path + "/data.txt", separator[0], repeatable, ignoreFirstLine, false)) return void (cout << failed << "Could not read the data." << endl);
            if (!import(path + "/custom.txt", ' ', false, false, true)) cout << "Could not read custom words for this dataset. Defaults to empty." << endl;
            if (!history->import()) cout << "Could not read history for this dataset. Defaults to empty." << endl;
            if (!favorites->import()) cout << "Could not read favorite list for this dataset. Defaults to empty." << endl;
            cout << "Sucessfully loaded data for the dictionary '" << name << "'!" << endl;
        }

        void reset () {
            for (string word : custom) remove(word);
            custom.clear();
        }

        void random () {
            return recursiveRandom(data);
        }

        void close () {
            history->save();
            favorites->save();
            ofstream fout (path + "/custom.txt");
            if (!fout.fail()) {
                for (string word : custom) {
                    Character* res = find(word);
                    if (res == NULL) continue;
                    fout << word << " " << res->definition[0] << endl;
                    if (res->definition.size() > 1) for (int i = 1; i < res->definition.size(); ++i) cout << res->definition[i] << endl;
                }
            }
            fout.close();
            delete data;
        }

        bool isEmpty () {
            return data->nextCharacters->isEmpty();
        }

        Dictionary (string namae, string dataPath): name(namae), path("data/" + dataPath) {
            history = new WordCollection(path + "/history.txt", true);
            favorites = new WordCollection(path + "/favorites.txt", false);
        };
        WordCollection *history, *favorites;
        vector <string> custom;
    private:
        Character *data = new Character(NULL);
        string path;
        Utils *utils = new Utils();

        void recursiveDelete (Word* node) {
            if (node == NULL) return;
            remove(node->word);
            recursiveDelete(node->left);
            recursiveDelete(node->right);
        }

        void show (Character *word) {
            cout << "Definition of the word '" << word->word << "':" << endl;
            word->display();
            history->add(word->word);
        }

        void recursiveRandom (Character *word) {
            if (word->nextCharacters->isEmpty()) return show(word);
            CharsetTree *tree = word->nextCharacters;
            vector <char> allChars = tree->toArray();
            int pool = allChars.size();
            if (word->isLastCharacter) ++pool;
            int randomizer = utils->randInt(pool);
            if (randomizer == allChars.size()) show(word);
            else recursiveRandom(tree->find(allChars[randomizer])->data);
        }
};

// Charset::~Charset () {
//     delete data;
//     if (left != NULL) delete left;
//     if (right != NULL) delete right;
// };

int CharsetTree::height (Charset* node) {
    return node == NULL ? 0 : node->height;
}

int CharsetTree::getBalance(Charset *node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

Charset* CharsetTree::leftRotate (Charset *node) {
    if (node == NULL) return node;
    Charset *y = node->right;
    Charset *T2 = y->left;
 
    // Perform rotation
    y->left = node;
    node->right = T2;
 
    // Update heights
    node->height = max(height(node->left),   
                    height(node->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}

Charset* CharsetTree::rightRotate (Charset* node) {
    if (node == NULL) return node;
    Charset *x = node->left;
    Charset *T2 = x->right;
 
    // Perform rotation
    x->right = node;
    node->left = T2;
 
    // Update heights
    node->height = max(height(node->left),
                    height(node->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}

Charset* CharsetTree::insert (Charset *node, char key, Character* &value) {
    if (node == NULL) return new Charset(key, value);
     if (key < node->key) node->left = insert(node->left, key, value);
    else if (key > node->key) node->right = insert(node->right, key, value);
    else {
        if (value->isLastCharacter) {
            node->data->isLastCharacter = true;
            for (string def : value->definition) node->data->definition.push_back(def);
            delete value;
            return node;
        }
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
       return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    else if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
};

Charset* CharsetTree::add (char key, Character* &value) {
    data = insert(data, key, value);
    return find(key);
}

Charset* CharsetTree::find (char key) {
    Charset *cur = data;
    while (cur != NULL) {
        if (key < cur->key) cur = cur->left;
        else if (key > cur->key) cur = cur->right;
        else break;
    }
    return cur;
};

Charset* CharsetTree::exclude (Charset* &node, char key) {
    if (node == NULL) return node;
    if ( key < node->key ) node->left = exclude(node->left, key);
    else if( key > node->key ) node->right = exclude(node->right, key);
    else {
        if (node->left == NULL || node->right == NULL) {
            Charset *temp = node->left != NULL ? node->left : node->right;
    
            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else *node = *temp;

            delete temp->data;
            delete temp;
        }
        else {
            Charset *minVal = node->right;
            while (minVal->left != NULL) minVal = minVal->left;

            node->key = minVal->key;
            node->data = minVal->data;

            node->right = exclude(node->right, minVal->key);
        }
    }

    if (node == NULL) return node;
 
    node->height = 1 + max(height(node->left), height(node->right));
 
    int balance = getBalance(node);
 
    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
 
    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
 
    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}

void CharsetTree::remove (char key) {
    return void (data = exclude(data, key));
}

bool CharsetTree::isEmpty () {
    return data == NULL;
}

vector<char> CharsetTree::toArray () {
    vector<char> arr;
    recursiveArray(arr, data);
    return arr;
}

void CharsetTree::recursiveArray (vector<char> &arr, Charset* node) {
    if (node == NULL) return;
    recursiveArray(arr, node->left);
    if (node->key != '\0') arr.push_back(node->key);
    recursiveArray(arr, node->right);
}

// CharsetTree::~CharsetTree () {
//     if (data != NULL) delete data;
// };

void Character::display () {
    cout << "Definition:" << endl;
    for (string def : definition) cout << " * " << def << endl;
};

Character* Character::next (char f) {
    Charset* found = nextCharacters->find(f);
    if (found == NULL) return NULL;
    return found->data;
};

// Character::~Character () {
//     delete nextCharacters;
// }