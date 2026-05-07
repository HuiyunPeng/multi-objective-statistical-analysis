#include <string>
#include <vector>
using namespace std;

bool cycpattern_check(string a, string b) {
    const size_t n = a.size(), m = b.size();
    if (m == 0 || m > n) return false;

    struct State {
        int len, link, head;
    };

    vector<State> st;
    vector<int> to, next;
    vector<unsigned char> ch;

    st.reserve(m * 4 + 1);
    to.reserve(m * 4 + 1);
    next.reserve(m * 4 + 1);
    ch.reserve(m * 4 + 1);

    auto newState = [&](int len) -> int {
        st.push_back({len, -1, -1});
        return (int)st.size() - 1;
    };

    auto addEdgeDirect = [&](int s, unsigned char c, int v) {
        ch.push_back(c);
        to.push_back(v);
        next.push_back(st[s].head);
        st[s].head = (int)ch.size() - 1;
    };

    auto findEdge = [&](int s, unsigned char c) -> int {
        for (int e = st[s].head; e != -1; e = next[e]) {
            if (ch[e] == c) return e;
        }
        return -1;
    };

    newState(0);
    int last = 0;

    auto extend = [&](unsigned char c) {
        int cur = newState(st[last].len + 1);
        int p = last, e = -1;

        while (p != -1 && (e = findEdge(p, c)) == -1) {
            addEdgeDirect(p, c, cur);
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = to[e];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = newState(st[p].len + 1);
                st[clone].link = st[q].link;

                for (int x = st[q].head; x != -1; x = next[x]) {
                    addEdgeDirect(clone, ch[x], to[x]);
                }

                while (p != -1) {
                    int ei = findEdge(p, c);
                    if (ei == -1 || to[ei] != q) break;
                    to[ei] = clone;
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    };

    for (unsigned char c : b) extend(c);
    for (unsigned char c : b) extend(c);

    int v = 0, l = 0;
    for (unsigned char c : a) {
        int e = findEdge(v, c);

        while (v != -1 && e == -1) {
            v = st[v].link;
            if (v != -1) {
                if (l > st[v].len) l = st[v].len;
                e = findEdge(v, c);
            }
        }

        if (v == -1) {
            v = 0;
            l = 0;
            continue;
        }

        v = to[e];
        ++l;
        if ((size_t)l >= m) return true;
    }

    return false;
}
