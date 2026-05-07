#include <vector>
using namespace std;

vector<float> get_positive(vector<float> l) {
    size_t write = 0;
    for (size_t read = 0; read < l.size(); ++read) {
        if (l[read] > 0) {
            l[write++] = l[read];
        }
    }
    l.resize(write);
    return l;
}
