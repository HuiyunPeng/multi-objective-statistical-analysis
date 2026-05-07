#include <vector>
using namespace std;

int smallest_change(vector<int> arr) {
    int out = 0;
    for (int i = 0, j = (int)arr.size() - 1; i < j; ++i, --j) {
        out += (arr[i] != arr[j]);
    }
    return out;
}
