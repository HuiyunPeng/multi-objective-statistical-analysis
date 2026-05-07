#include <vector>
#include <algorithm>

std::vector<int> unique(std::vector<int> l) {
    if (l.size() <= 1) return l;
    std::sort(l.begin(), l.end());
    l.erase(std::unique(l.begin(), l.end()), l.end());
    return l;
}
