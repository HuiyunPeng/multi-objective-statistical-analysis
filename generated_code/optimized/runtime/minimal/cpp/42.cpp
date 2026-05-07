#include <vector>
using namespace std;

vector<int> incr_list(vector<int> l) {
    if (!l.empty()) {
        int* p = l.data();
        int* end = p + l.size();
        do {
            ++(*p);
        } while (++p != end);
    }
    return l;
}
