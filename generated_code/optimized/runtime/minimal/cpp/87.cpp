#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
#include <algorithm>
#include <stdlib.h>

vector<vector<int>> get_row(vector<vector<int>> lst, int x) {
    vector<vector<int>> out;
    out.reserve(lst.size());

    const int n = (int)lst.size();
    for (int i = 0; i < n; ++i) {
        const vector<int>& row = lst[i];
        for (int j = (int)row.size() - 1; j >= 0; --j) {
            if (row[j] == x) {
                out.push_back({i, j});
            }
        }
    }
    return out;
}
