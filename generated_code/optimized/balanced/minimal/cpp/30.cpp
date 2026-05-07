#include <vector>
using namespace std;

vector<float> get_positive(vector<float> l) {
    size_t write = 0;
    const size_t n = l.size();
    for (size_t read = 0; read < n; ++read) {
        if (l[read] > 0.0f) {
            l[write++] = l[read];
        }
    }
    l.resize(write);
    return l;
}
