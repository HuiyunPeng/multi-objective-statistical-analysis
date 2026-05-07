#include <vector>
#include <algorithm>
using namespace std;

vector<int> strange_sort_list(vector<int> lst) {
    sort(lst.begin(), lst.end());
    const int n = (int)lst.size();
    if (n < 2) return lst;

    vector<bool> visited(n, false);

    for (int start = 0; start < n; ++start) {
        if (visited[start]) continue;

        int temp = lst[start];
        int cur = start;

        while (!visited[cur]) {
            visited[cur] = true;

            int next;
            if (cur <= (n - 1) / 2) {
                next = cur * 2;
            } else {
                next = (n - 1 - cur) * 2 + 1;
            }

            swap(temp, lst[next]);
            cur = next;
        }
    }

    return lst;
}
