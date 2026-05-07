#include <string>
using namespace std;

string sort_numbers(string numbers) {
    static const char* names[10] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine"
    };

    int count[10] = {0};
    const int n = (int)numbers.size();

    for (int i = 0; i < n; ) {
        int start = i;
        while (i < n && numbers[i] != ' ') ++i;

        switch (numbers[start]) {
            case 'z': ++count[0]; break; // zero
            case 'o': ++count[1]; break; // one
            case 't': ++count[numbers[start + 1] == 'w' ? 2 : 3]; break; // two, three
            case 'f': ++count[numbers[start + 1] == 'o' ? 4 : 5]; break; // four, five
            case 's': ++count[numbers[start + 1] == 'i' ? 6 : 7]; break; // six, seven
            case 'e': ++count[8]; break; // eight
            case 'n': ++count[9]; break; // nine
        }

        while (i < n && numbers[i] == ' ') ++i;
    }

    string out;
    out.reserve(numbers.size());

    bool first = true;
    for (int d = 0; d < 10; ++d) {
        for (int c = 0; c < count[d]; ++c) {
            if (!first) out.push_back(' ');
            out += names[d];
            first = false;
        }
    }

    return out;
}
