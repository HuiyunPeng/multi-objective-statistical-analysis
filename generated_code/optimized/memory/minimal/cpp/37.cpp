#include <vector>
using namespace std;

vector<float> sort_even(vector<float> l) {
    for (size_t i = 2; i < l.size(); i += 2) {
        float key = l[i];
        size_t j = i;
        while (j >= 2 && l[j - 2] > key) {
            l[j] = l[j - 2];
            j -= 2;
        }
        l[j] = key;
    }
    return l;
}
