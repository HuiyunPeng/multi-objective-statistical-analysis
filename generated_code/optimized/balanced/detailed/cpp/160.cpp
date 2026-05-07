#include <vector>
#include <string>
#include <cmath>

using namespace std;

int do_algebra(vector<string> operato, vector<int> operand) {
    size_t opCount = operato.size();

    // First pass: evaluate "**" left-to-right, compact others in-place.
    {
        size_t writeOp = 0;
        int current = operand[0];

        for (size_t i = 0; i < opCount; ++i) {
            const string& op = operato[i];
            if (op[0] == '*' && op.size() == 2) {
                current = static_cast<int>(pow(current, operand[i + 1]));
            } else {
                operand[writeOp] = current;
                if (writeOp != i) operato[writeOp] = op;
                ++writeOp;
                current = operand[i + 1];
            }
        }

        operand[writeOp] = current;
        opCount = writeOp;
    }

    // Second pass: evaluate "*" and "//" left-to-right, compact "+" and "-" in-place.
    {
        size_t writeOp = 0;
        int current = operand[0];

        for (size_t i = 0; i < opCount; ++i) {
            const char c = operato[i][0];
            if (c == '*' || c == '/') {
                if (c == '*')
                    current *= operand[i + 1];
                else
                    current /= operand[i + 1];
            } else {
                operand[writeOp] = current;
                if (writeOp != i) operato[writeOp] = operato[i];
                ++writeOp;
                current = operand[i + 1];
            }
        }

        operand[writeOp] = current;
        opCount = writeOp;
    }

    // Final pass: evaluate "+" and "-" left-to-right.
    int result = operand[0];
    for (size_t i = 0; i < opCount; ++i) {
        if (operato[i][0] == '+')
            result += operand[i + 1];
        else
            result -= operand[i + 1];
    }

    return result;
}
