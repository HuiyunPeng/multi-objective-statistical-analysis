#include <string>

using std::string;

inline int strlen(string str) noexcept {
    return static_cast<int>(str.size());
}
