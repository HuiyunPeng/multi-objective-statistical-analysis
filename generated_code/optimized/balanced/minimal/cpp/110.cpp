#include <vector>
#include <string>

std::string exchange(std::vector<int> lst1, std::vector<int> lst2) {
    const std::size_t need = lst1.size();
    if (need == 0) return "YES";

    std::size_t num = 0;

    for (int x : lst1) {
        num += ((x & 1) == 0);
        if (num >= need) return "YES";
    }

    for (int x : lst2) {
        num += ((x & 1) == 0);
        if (num >= need) return "YES";
    }

    return "NO";
}
