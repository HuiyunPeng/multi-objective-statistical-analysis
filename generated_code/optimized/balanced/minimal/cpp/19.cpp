#include <string>

using namespace std;

string sort_numbers(string numbers) {
    if (numbers.empty()) return "";

    size_t count[10] = {};
    const size_t n = numbers.size();
    size_t start = 0;

    for (size_t i = 0; i <= n; ++i) {
        if (i == n || numbers[i] == ' ') {
            const size_t len = i - start;
            int d = 0;

            switch (len) {
                case 3:
                    if (numbers[start] == 'o' && numbers[start + 1] == 'n' && numbers[start + 2] == 'e') d = 1;
                    else if (numbers[start] == 't' && numbers[start + 1] == 'w' && numbers[start + 2] == 'o') d = 2;
                    else if (numbers[start] == 's' && numbers[start + 1] == 'i' && numbers[start + 2] == 'x') d = 6;
                    break;
                case 4:
                    if (numbers[start] == 'z' && numbers[start + 1] == 'e' && numbers[start + 2] == 'r' && numbers[start + 3] == 'o') d = 0;
                    else if (numbers[start] == 'f' && numbers[start + 1] == 'o' && numbers[start + 2] == 'u' && numbers[start + 3] == 'r') d = 4;
                    else if (numbers[start] == 'f' && numbers[start + 1] == 'i' && numbers[start + 2] == 'v' && numbers[start + 3] == 'e') d = 5;
                    else if (numbers[start] == 'n' && numbers[start + 1] == 'i' && numbers[start + 2] == 'n' && numbers[start + 3] == 'e') d = 9;
                    break;
                case 5:
                    if (numbers[start] == 't' && numbers[start + 1] == 'h' && numbers[start + 2] == 'r' && numbers[start + 3] == 'e' && numbers[start + 4] == 'e') d = 3;
                    else if (numbers[start] == 's' && numbers[start + 1] == 'e' && numbers[start + 2] == 'v' && numbers[start + 3] == 'e' && numbers[start + 4] == 'n') d = 7;
                    else if (numbers[start] == 'e' && numbers[start + 1] == 'i' && numbers[start + 2] == 'g' && numbers[start + 3] == 'h' && numbers[start + 4] == 't') d = 8;
                    break;
                default:
                    break;
            }

            ++count[d];
            start = i + 1;
        }
    }

    static const char* words[10] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine"
    };
    static const unsigned char lens[10] = {4, 3, 3, 5, 4, 4, 3, 5, 5, 4};

    size_t total_words = 0, total_len = 0;
    for (int i = 0; i < 10; ++i) {
        total_words += count[i];
        total_len += count[i] * lens[i];
    }
    if (total_words > 1) total_len += total_words - 1;

    string out;
    out.reserve(total_len);

    bool first = true;
    for (int i = 0; i < 10; ++i) {
        for (size_t j = 0; j < count[i]; ++j) {
            if (!first) out.push_back(' ');
            first = false;
            out += words[i];
        }
    }

    return out;
}
