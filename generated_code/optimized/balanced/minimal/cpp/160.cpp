#include <vector>
#include <string>
#include <cmath>

using namespace std;

static inline int fast_pow_int(int base, int exp) {
    if (exp < 0) {
        return static_cast<int>(pow(base, exp));
    }
    int result = 1;
    while (exp) {
        if (exp & 1) result *= base;
        exp >>= 1;
        if (exp) base *= base;
    }
    return result;
}

int do_algebra(vector<string> operato, vector<int> operand) {
    if (operand.empty()) return 0;

    int m = static_cast<int>(operato.size());
    if (m == 0) return operand[0];

    // Pass 1: exponentiation
    int wv = 0, wo = 0;
    int cur = operand[0];
    for (int i = 0; i < m; ++i) {
        const string& op = operato[i];
        if (op.size() == 2 && op[0] == '*') {
            cur = fast_pow_int(cur, operand[i + 1]);
        } else {
            operand[wv++] = cur;
            operato[wo++] = op;
            cur = operand[i + 1];
        }
    }
    operand[wv++] = cur;
    m = wo;

    if (m == 0) return operand[0];

    // Pass 2: multiplication and integer division
    int new_wv = 0, new_wo = 0;
    cur = operand[0];
    for (int i = 0; i < m; ++i) {
        const string& op = operato[i];
        if (op[0] == '*') {
            cur *= operand[i + 1];
        } else if (op[0] == '/') {
            cur /= operand[i + 1];
        } else {
            operand[new_wv++] = cur;
            operato[new_wo++] = op;
            cur = operand[i + 1];
        }
    }
    operand[new_wv++] = cur;
    m = new_wo;

    if (m == 0) return operand[0];

    // Pass 3: addition and subtraction
    int result = operand[0];
    for (int i = 0; i < m; ++i) {
        if (operato[i][0] == '+') {
            result += operand[i + 1];
        } else {
            result -= operand[i + 1];
        }
    }

    return result;
}
