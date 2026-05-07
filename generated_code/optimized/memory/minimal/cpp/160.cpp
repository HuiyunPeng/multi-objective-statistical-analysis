#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
#include <algorithm>
#include <stdlib.h>

int do_algebra(vector<string> operato, vector<int> operand) {
    int opCount = (int)operato.size();
    if (operand.empty()) return 0;

    int write = 0;
    for (int i = 0; i < opCount; ++i) {
        if (operato[i] == "**") {
            operand[write] = (int)pow(operand[write], operand[i + 1]);
        } else {
            operato[write] = operato[i];
            operand[++write] = operand[i + 1];
        }
    }
    opCount = write;

    write = 0;
    for (int i = 0; i < opCount; ++i) {
        if (operato[i] == "*") {
            operand[write] = operand[write] * operand[i + 1];
        } else if (operato[i] == "//") {
            operand[write] = operand[write] / operand[i + 1];
        } else {
            operato[write] = operato[i];
            operand[++write] = operand[i + 1];
        }
    }
    opCount = write;

    write = 0;
    for (int i = 0; i < opCount; ++i) {
        if (operato[i] == "+") {
            operand[write] = operand[write] + operand[i + 1];
        } else {
            operand[write] = operand[write] - operand[i + 1];
        }
    }

    return operand[0];
}
