#include <string>
#include <cstring>

std::string sort_numbers(std::string numbers) {
    static const char* const words[10] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine"
    };
    static const unsigned char lens[10] = {4, 3, 3, 5, 4, 4, 3, 5, 5, 4};

    int counts[10] = {};
    const size_t n = numbers.size();

    size_t start = 0;
    for (size_t i = 0; i <= n; ++i) {
        if (i == n || numbers[i] == ' ') {
            const size_t len = i - start;
            if (len != 0) {
                int digit;
                switch (numbers[start]) {
                    case 'z': digit = 0; break;
                    case 'o': digit = 1; break;
                    case 't': digit = (numbers[start + 1] == 'w') ? 2 : 3; break;
                    case 'f': digit = (numbers[start + 1] == 'o') ? 4 : 5; break;
                    case 's': digit = (numbers[start + 1] == 'i') ? 6 : 7; break;
                    case 'e': digit = 8; break;
                    default:  digit = 9; break;
                }
                ++counts[digit];
            }
            start = i + 1;
        }
    }

    size_t total_words = 0;
    size_t total_len = 0;
    for (int i = 0; i < 10; ++i) {
        total_words += counts[i];
        total_len += static_cast<size_t>(counts[i]) * lens[i];
    }

    if (total_words == 0) return std::string();
    total_len += total_words - 1;

    std::string out;
    out.resize(total_len);

    size_t pos = 0;
    for (int i = 0; i < 10; ++i) {
        for (int c = 0; c < counts[i]; ++c) {
            if (pos) out[pos++] = ' ';
            std::memcpy(&out[pos], words[i], lens[i]);
            pos += lens[i];
        }
    }

    return out;
}
