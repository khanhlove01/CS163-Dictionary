#include <random>

using namespace std;

class Utils {
public:
    int randIntInRange (int start, int end) {
        // https://stackoverflow.com/questions/43432014/c-generate-random-number-every-time/43432296#43432296
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dis(start, end);
        return dis(gen);
    }

    int randInt (int range) {
        return randIntInRange(0, range);
    }
};