#include <vector>
using namespace std;

vector<float> get_positive(vector<float> l) {
    vector<float>::size_type write = 0;
    for (vector<float>::size_type read = 0; read < l.size(); ++read) {
        if (l[read] > 0) {
            l[write++] = l[read];
        }
    }
    l.resize(write);
    return l;
}
