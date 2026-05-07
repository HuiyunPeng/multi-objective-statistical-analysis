#include <vector>
#include <algorithm>
using namespace std;

vector<float> get_positive(vector<float> l) {
    l.erase(remove_if(l.begin(), l.end(), [](float x) { return x <= 0.0f; }), l.end());
    return l;
}
