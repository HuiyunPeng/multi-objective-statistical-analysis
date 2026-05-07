#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string intersection(vector<int> interval1, vector<int> interval2) {
    const int inter1 = max(interval1[0], interval2[0]);
    const int inter2 = min(interval1[1], interval2[1]);
    const int l = inter2 - inter1;

    if (l < 2) return "NO";
    if (l == 2) return "YES";
    if ((l & 1) == 0) return "NO";

    for (int i = 3; i <= l / i; i += 2) {
        if (l % i == 0) return "NO";
    }
    return "YES";
}
