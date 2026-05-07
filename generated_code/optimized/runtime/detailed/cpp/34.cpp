#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
#include <stdlib.h>

vector<int> unique(vector<int> l) {
    if (l.size() <= 1) return l;
    sort(l.begin(), l.end());
    l.erase(std::unique(l.begin(), l.end()), l.end());
    return l;
}
