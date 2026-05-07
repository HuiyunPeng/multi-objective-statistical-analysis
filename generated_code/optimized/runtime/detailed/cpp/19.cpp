#include <string>
using namespace std;

string sort_numbers(string numbers) {
    static const string words[10] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine"
    };

    int count[10] = {0};
    const int n = static_cast<int>(numbers.size());

    for (int i = 0; i < n;) {
        while (i < n && numbers[i] == ' ') ++i;
        if (i >= n) break;

        const int start = i;
        while (i < n && numbers[i] != ' ') ++i;
        const int len = i - start;

        int digit;
        switch (numbers[start]) {
            case 'z': digit = 0; break;          // zero
            case 'o': digit = 1; break;          // one
            case 't': digit = (len == 3) ? 2 : 3; break; // two, three
            case 'f': digit = (len == 4) ? 4 : 5; break; // four, five
            case 's': digit = (len == 3) ? 6 : 7; break; // six, seven
            case 'e': digit = 8; break;          // eight
            default:  digit = 9; break;          // nine
        }
        ++count[digit];
    }

    int totalCount = 0;
    size_t totalLen = 0;
    for (int i = 0; i < 10; ++i) {
        totalCount += count[i];
        totalLen += static_cast<size_t>(count[i]) * words[i].size();
    }

    if (totalCount == 0) return "";

    totalLen += static_cast<size_t>(totalCount - 1);
    string out;
    out.reserve(totalLen);

    bool first = true;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            if (!first) out.push_back(' ');
            first = false;
            out += words[i];
        }
    }

    return out;
}
