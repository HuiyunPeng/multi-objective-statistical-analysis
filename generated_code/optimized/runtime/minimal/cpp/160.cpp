#include <vector>
#include <string>
#include <cmath>
using namespace std;

int do_algebra(vector<string> operato, vector<int> operand) {
    const int m = static_cast<int>(operato.size());
    if (operand.empty()) return 0;

    int wVal = 1, wOp = 0;
    for (int i = 0; i < m; ++i) {
        const string &op = operato[i];
        if (op[0] == '*' && op.size() == 2) {
            operand[wVal - 1] = static_cast<int>(pow(operand[wVal - 1], operand[i + 1]));
        } else {
            operato[wOp++] = op;
            operand[wVal++] = operand[i + 1];
        }
    }

    int m1 = wOp;
    int wVal2 = 1, wOp2 = 0;
    for (int i = 0; i < m1; ++i) {
        const string &op = operato[i];
        const char c = op[0];
        if (c == '*' && op.size() == 1) {
            operand[wVal2 - 1] *= operand[i + 1];
        } else if (c == '/') {
            operand[wVal2 - 1] /= operand[i + 1];
        } else {
            operato[wOp2++] = op;
            operand[wVal2++] = operand[i + 1];
        }
    }

    int result = operand[0];
    for (int i = 0; i < wOp2; ++i) {
        if (operato[i][0] == '+')
            result += operand[i + 1];
        else
            result -= operand[i + 1];
    }

    return result;
}
