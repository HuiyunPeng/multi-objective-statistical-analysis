#include <string>
#include <vector>
using namespace std;

bool cycpattern_check(string a, string b) {
    const int n = (int)a.size();
    const int m = (int)b.size();

    if (m == 0 || n < m) return false;

    struct State {
        int next[256];
        int link;
        int len;
        State() : link(-1), len(0) {
            for (int i = 0; i < 256; ++i) next[i] = -1;
        }
    };

    vector<State> st(2 * n);
    int sz = 1, last = 0;

    for (int i = 0; i < n; ++i) {
        const int c = (unsigned char)a[i];
        int cur = sz++;
        st[cur].len = st[last].len + 1;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone] = st[q];
                st[clone].len = st[p].len + 1;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    }

    int v = 0, l = 0;
    const int limit = 2 * m - 1;

    for (int i = 0; i < limit; ++i) {
        const int c = (unsigned char)b[i < m ? i : i - m];

        while (v && st[v].next[c] == -1) {
            v = st[v].link;
            l = st[v].len;
        }

        if (st[v].next[c] != -1) {
            v = st[v].next[c];
            ++l;
        } else {
            v = 0;
            l = 0;
        }

        if (i >= m - 1 && l >= m) return true;
    }

    return false;
}
