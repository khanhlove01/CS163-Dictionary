using namespace std;

class ConsoleOperation {
    public:
        void clear () {
            cout << "\x1B[2J\x1B[H";
        }
        void pause () {
            cout << "Press any key to continue... ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
};