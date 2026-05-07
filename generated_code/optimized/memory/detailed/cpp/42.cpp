#include <vector>
using namespace std;

vector<int> incr_list(vector<int> l) {
    for (int& x : l) {
        ++x;
    }
    return l;
}
