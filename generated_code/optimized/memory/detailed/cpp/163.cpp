#include <vector>
using namespace std;

vector<int> generate_integers(int a, int b) {
    if (b < a) {
        int m = a;
        a = b;
        b = m;
    }

    const int end = (b < 10) ? b : 9;
    int start = (a % 2 == 0) ? a : (a + 1);

    if (start > end) {
        return vector<int>();
    }

    vector<int> out;
    out.reserve((end - start) / 2 + 1);

    for (int i = start; i <= end; i += 2) {
        out.push_back(i);
    }

    return out;
}
