#include <vector>

std::vector<int> incr_list(std::vector<int> l) {
    int* p = l.data();
    int* e = p + l.size();
    while (p != e) {
        ++(*p);
        ++p;
    }
    return l;
}
