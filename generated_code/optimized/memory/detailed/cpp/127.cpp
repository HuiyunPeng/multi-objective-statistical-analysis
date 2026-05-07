#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string intersection(vector<int> interval1, vector<int> interval2) {
    const int l = min(interval1[1], interval2[1]) - max(interval1[0], interval2[0]);
    if (l < 2) return "NO";
    for (int i = 2; i * i <= l; ++i) {
        if (l % i == 0) return "NO";
    }
    return "YES";
}
