#include "unistd.h"
#include "string"

using namespace std;

class ConsoleOperation {
    public:
        void clear () {
            safeHandler("CLS");
            safeHandler("clear");
        }
        void pause () {
            safeHandler("pause");
            safeHandler("read");
        }
    private:
        void safeHandler (const char *command) {
            int duperr;
            duperr = dup(2);
            close(2); /* close stderr so the new process can't output the error */
            system(command);
            dup2(duperr, 2);
            close(duperr);
        }
};