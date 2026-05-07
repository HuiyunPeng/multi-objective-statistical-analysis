#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string intersection(vector<int> interval1, vector<int> interval2) {
    const int inter1 = interval1[0] > interval2[0] ? interval1[0] : interval2[0];
    const int inter2 = interval1[1] < interval2[1] ? interval1[1] : interval2[1];
    const int l = inter2 - inter1;

    if (l <= 1) return "NO";
    if (l <= 3) return "YES";
    if ((l & 1) == 0 || l % 3 == 0) return "NO";

    for (int i = 5; 1LL * i * i <= l; i += 6) {
        if (l % i == 0 || l % (i + 2) == 0) return "NO";
    }
    return "YES";
}
