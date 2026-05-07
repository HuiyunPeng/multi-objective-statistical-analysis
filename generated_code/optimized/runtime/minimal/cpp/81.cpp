#include <vector>
#include <string>
using namespace std;

vector<string> numerical_letter_grade(vector<float> grades) {
    vector<string> out;
    out.reserve(grades.size());

    for (size_t i = 0, n = grades.size(); i < n; ++i) {
        const float g = grades[i];

        if (g >= 3.9999f) out.emplace_back("A+");
        else if (g > 3.7001f) out.emplace_back("A");
        else if (g > 3.3001f) out.emplace_back("A-");
        else if (g > 3.0001f) out.emplace_back("B+");
        else if (g > 2.7001f) out.emplace_back("B");
        else if (g > 2.3001f) out.emplace_back("B-");
        else if (g > 2.0001f) out.emplace_back("C+");
        else if (g > 1.7001f) out.emplace_back("C");
        else if (g > 1.3001f) out.emplace_back("C-");
        else if (g > 1.0001f) out.emplace_back("D+");
        else if (g > 0.7001f) out.emplace_back("D");
        else if (g > 0.0001f) out.emplace_back("D-");
        else out.emplace_back("E");
    }

    return out;
}
