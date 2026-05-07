#include <string>

using namespace std;

static inline int word_to_digit(const string& s, size_t start, size_t len) {
    switch (len) {
        case 3:
            if (s[start] == 'o') return 1; // one
            if (s[start] == 't') return 2; // two
            return 6;                      // six
        case 4:
            switch (s[start]) {
                case 'z': return 0; // zero
                case 'f': return 4; // four
                case 'f': break;
                case 'n': return 9; // nine
            }
            return 5;               // five
        case 5:
            if (s[start] == 't') return 3; // three
            if (s[start] == 's') return 7; // seven
            return 8;                      // eight
    }
    return 0;
}

string sort_numbers(string numbers) {
    static const char* words[10] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine"
    };

    int count[10] = {0};

    const size_t n = numbers.size();
    size_t start = 0;

    while (start < n) {
        size_t end = start;
        while (end < n && numbers[end] != ' ') ++end;
        ++count[word_to_digit(numbers, start, end - start)];
        start = end + 1;
    }

    numbers.clear();

    bool first = true;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            if (!first) numbers.push_back(' ');
            first = false;
            numbers += words[i];
        }
    }

    return numbers;
}
