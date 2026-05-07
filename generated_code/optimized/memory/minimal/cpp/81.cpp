#include <vector>
#include <string>
using namespace std;

vector<string> numerical_letter_grade(vector<float> grades) {
    vector<string> out(grades.size());

    for (size_t i = 0; i < grades.size(); ++i) {
        float g = grades[i];

        if (g >= 3.9999f) out[i] = "A+";
        else if (g > 3.7001f) out[i] = "A";
        else if (g > 3.3001f) out[i] = "A-";
        else if (g > 3.0001f) out[i] = "B+";
        else if (g > 2.7001f) out[i] = "B";
        else if (g > 2.3001f) out[i] = "B-";
        else if (g > 2.0001f) out[i] = "C+";
        else if (g > 1.7001f) out[i] = "C";
        else if (g > 1.3001f) out[i] = "C-";
        else if (g > 1.0001f) out[i] = "D+";
        else if (g > 0.7001f) out[i] = "D";
        else if (g > 0.0001f) out[i] = "D-";
        else out[i] = "E";
    }

    return out;
}
