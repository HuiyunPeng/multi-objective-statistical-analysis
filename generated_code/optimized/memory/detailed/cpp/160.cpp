#include <vector>
#include <string>
#include <cmath>
using namespace std;

int do_algebra(vector<string> operato, vector<int> operand) {
    if (operand.empty()) return 0;

    size_t opCount = operato.size();
    size_t w = 0;

    for (size_t i = 0; i < opCount; ++i) {
        const string& op = operato[i];
        if (op == "**") {
            operand[w] = static_cast<int>(pow(operand[w], operand[i + 1]));
        } else {
            ++w;
            operand[w] = operand[i + 1];
            operato[w - 1] = op;
        }
    }
    opCount = w;

    w = 0;
    for (size_t i = 0; i < opCount; ++i) {
        const string& op = operato[i];
        if (op == "*") {
            operand[w] *= operand[i + 1];
        } else if (op == "//") {
            operand[w] /= operand[i + 1];
        } else {
            ++w;
            operand[w] = operand[i + 1];
            operato[w - 1] = op;
        }
    }
    opCount = w;

    for (size_t i = 0; i < opCount; ++i) {
        if (operato[i] == "+") {
            operand[0] += operand[i + 1];
        } else {
            operand[0] -= operand[i + 1];
        }
    }

    return operand[0];
}
