#include <vector>
#include <algorithm>
using namespace std;

vector<int> maximum(vector<int> arr, int k) {
    sort(arr.begin(), arr.end());
    arr.erase(arr.begin(), arr.end() - k);
    return arr;
}
