#include <string>
#include <vector>
#include <utility>
using namespace std;

bool cycpattern_check(string a, string b) {
    const int m = (int)b.size();
    if (m == 0) return false;
    if ((int)a.size() < m) return false;

    const string s = b + b;

    struct State {
        int link = -1;
        int len = 0;
        vector<pair<unsigned char, int>> next;
    };

    vector<State> st;
    st.reserve(s.size() * 2 + 1);
    st.push_back(State());

    auto get_transition = [&](int v, unsigned char c) -> int {
        const auto& nx = st[v].next;
        for (const auto& e : nx) {
            if (e.first == c) return e.second;
        }
        return -1;
    };

    auto set_transition = [&](int v, unsigned char c, int to) {
        auto& nx = st[v].next;
        for (auto& e : nx) {
            if (e.first == c) {
                e.second = to;
                return;
            }
        }
        nx.emplace_back(c, to);
    };

    int last = 0;
    for (unsigned char c : s) {
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;

        int p = last;
        while (p != -1 && get_transition(p, c) == -1) {
            set_transition(p, c, cur);
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = get_transition(p, c);
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;

                while (p != -1 && get_transition(p, c) == q) {
                    set_transition(p, c, clone);
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    }

    int v = 0, l = 0;
    for (unsigned char c : a) {
        int to = get_transition(v, c);
        if (to != -1) {
            v = to;
            ++l;
        } else {
            while (v != -1 && (to = get_transition(v, c)) == -1) {
                v = st[v].link;
            }
            if (v == -1) {
                v = 0;
                l = 0;
                continue;
            }
            l = st[v].len + 1;
            v = to;
        }

        if (l >= m) return true;
    }

    return false;
}
