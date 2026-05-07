#include <string>
using namespace std;

string sort_numbers(string numbers) {
    static const char* words[10] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine"
    };
    static const int lens[10] = {4, 3, 3, 5, 4, 4, 3, 5, 5, 4};

    int count[10] = {0};
    const int n = static_cast<int>(numbers.size());

    int i = 0;
    while (i < n) {
        while (i < n && numbers[i] == ' ') ++i;
        if (i >= n) break;

        int start = i;
        while (i < n && numbers[i] != ' ') ++i;
        int len = i - start;

        switch (numbers[start]) {
            case 'z': ++count[0]; break;
            case 'o': ++count[1]; break;
            case 't': ++count[(len == 3) ? 2 : 3]; break;
            case 'f': ++count[(numbers[start + 1] == 'o') ? 4 : 5]; break;
            case 's': ++count[(len == 3) ? 6 : 7]; break;
            case 'e': ++count[8]; break;
            case 'n': ++count[9]; break;
        }
    }

    int total = 0, outLen = 0;
    for (int d = 0; d < 10; ++d) {
        total += count[d];
        outLen += count[d] * lens[d];
    }
    if (total == 0) return "";

    outLen += total - 1;
    string out;
    out.reserve(outLen);

    bool first = true;
    for (int d = 0; d < 10; ++d) {
        for (int c = 0; c < count[d]; ++c) {
            if (!first) out += ' ';
            out += words[d];
            first = false;
        }
    }

    return out;
}
