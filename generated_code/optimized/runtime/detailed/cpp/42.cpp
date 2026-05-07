#include <vector>
using namespace std;

vector<int> incr_list(vector<int> l) {
    int* data = l.data();
    const size_t n = l.size();
    for (size_t i = 0; i < n; ++i) {
        ++data[i];
    }
    return l;
}
