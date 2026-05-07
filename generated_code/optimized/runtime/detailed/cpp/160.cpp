#include <vector>
#include <string>
#include <cmath>
using namespace std;

int do_algebra(vector<string> operato, vector<int> operand) {
    const int nOps = (int)operato.size();
    if (nOps == 0) return operand[0];

    vector<int> parent(operand.size());
    for (int i = 0, n = (int)parent.size(); i < n; ++i) parent[i] = i;

    vector<unsigned char> code(nOps, 255);
    vector<int> expIdx, mdIdx, asIdx;
    expIdx.reserve(nOps);
    mdIdx.reserve(nOps);
    asIdx.reserve(nOps);

    for (int i = 0; i < nOps; ++i) {
        const string& s = operato[i];
        if (s.size() == 2) {
            if (s[0] == '*' && s[1] == '*') {
                code[i] = 0;
                expIdx.push_back(i);
            } else if (s[0] == '/' && s[1] == '/') {
                code[i] = 2;
                mdIdx.push_back(i);
            }
        } else if (s.size() == 1) {
            if (s[0] == '*') {
                code[i] = 1;
                mdIdx.push_back(i);
            } else if (s[0] == '+') {
                code[i] = 3;
                asIdx.push_back(i);
            } else if (s[0] == '-') {
                code[i] = 4;
                asIdx.push_back(i);
            }
        }
    }

    int* vals = operand.data();
    int* par = parent.data();

    auto find_root = [&](int x) {
        while (par[x] != x) {
            par[x] = par[par[x]];
            x = par[x];
        }
        return x;
    };

    for (int idx : expIdx) {
        const int left = find_root(idx);
        const int right = find_root(idx + 1);
        vals[left] = (int)pow((double)vals[left], (double)vals[right]);
        par[right] = left;
    }

    for (int idx : mdIdx) {
        const int left = find_root(idx);
        const int right = find_root(idx + 1);
        if (code[idx] == 1)
            vals[left] *= vals[right];
        else
            vals[left] /= vals[right];
        par[right] = left;
    }

    for (int idx : asIdx) {
        const int left = find_root(idx);
        const int right = find_root(idx + 1);
        if (code[idx] == 3)
            vals[left] += vals[right];
        else
            vals[left] -= vals[right];
        par[right] = left;
    }

    return vals[find_root(0)];
}
