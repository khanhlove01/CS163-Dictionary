#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Word {
public:
    string word;
    int order, height;
    Word *left, *right;

    Word(int No, string kotoba): left(NULL), right(NULL), word(kotoba), order(No), height(1) {}
};

struct WordCollection {
public:
    WordCollection(): root(NULL) {}
    ~WordCollection() {
        destroy(root);
    }

    bool add (string word) {
        int lastOrder = queueOrder;
        root = insert(root, queueOrder + 1, word);
        return queueOrder != lastOrder;
    }

    bool remove (string word) {
        Word* res = find(word);
        if (res == NULL) return false;
        root = exclude(root, res->order);
        return true;
    }

    Word *find (string word) {
        return recursiveFind(word, root);
    }

    bool isEmpty () {
        return root == NULL;
    }

    bool import () {
        ifstream fin(path);
        if (fin.fail()) {
            fin.close();
            return false;
        }
        else while (!fin.eof()) {
            string line;
            getline(fin, line);
            if (line != "") add(line);
        }
        fin.close();
        return true;
    }

    void display(ostream &stream) {
        recusrionExport(root, stream);
    }

    void save () {
        ofstream fout(path);
        if (fout.fail()) return;
        display(fout);
        fout.close();
    }

    WordCollection (string dataPath, bool isDup): path(dataPath), allowDuplicates(isDup) {};

    Word *root = NULL;
private:

    string path;

    int queueOrder = 0;

    bool allowDuplicates;

    Word *insert (Word *node, int key, string value) {
        if (node == NULL) {
            ++queueOrder;
            return new Word(key, value);
        }
        if (!allowDuplicates && node->word == value) return node;
        if (key < node->order) node->left = insert(node->left, key, value);
        else if (key > node->order) node->right = insert(node->right, key, value);

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->order)
        return rightRotate(node);
    
        // Right Right Case
        if (balance < -1 && key > node->right->order)
            return leftRotate(node);
    
        // Left Right Case
        else if (balance > 1 && key > node->left->order)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    
        // Right Left Case
        if (balance < -1 && key < node->right->order)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    };

    int height (Word* node) {
        return node == NULL ? 0 : node->height;
    }

    int getBalance(Word *node) {
        if (node == NULL) return 0;
        return height(node->left) - height(node->right);
    }

    Word *leftRotate (Word *node) {
        if (node == NULL) return node;
        Word *y = node->right;
        Word *T2 = y->left;
    
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

    Word *rightRotate (Word* node) {
        if (node == NULL) return node;
        Word *x = node->left;
        Word *T2 = x->right;
    
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

    Word *exclude (Word* &node, char key) {
        if (node == NULL) return node;
        if ( key < node->order ) node->left = exclude(node->left, key);
        else if( key > node->order ) node->right = exclude(node->right, key);
        else {
            if (node->left == NULL || node->right == NULL) {
                Word *temp = node->left != NULL ? node->left : node->right;
        
                if (temp == NULL)
                {
                    temp = node;
                    node = NULL;
                }
                else *node = *temp;

                delete temp;
            }
            else {
                Word *minVal = node->right;
                while (minVal->left != NULL) minVal = minVal->left;

                node->order = minVal->order;

                node->right = exclude(node->right, minVal->order);
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

    Word *recursiveFind(string word, Word *node) {
        if (node == NULL) return NULL;
        if (node->word == word) return node;
        Word *leftRes = recursiveFind(word, node->left), *rightRes = recursiveFind(word, node->right);
        if (leftRes != NULL) return leftRes;
        return rightRes;
    }

    void recusrionExport(Word *node, ostream &fout) {
        if (node == NULL) return;
        recusrionExport(node->left, fout);
        fout << node->word << endl;
        recusrionExport(node->right, fout); 
    }

    void destroy(Word *&node) {
        if (node == NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};