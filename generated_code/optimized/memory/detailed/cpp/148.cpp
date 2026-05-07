#include <vector>
#include <string>
using namespace std;

vector<string> bf(string planet1, string planet2) {
    static const char* const planets[] = {
        "Mercury", "Venus", "Earth", "Mars",
        "Jupiter", "Saturn", "Uranus", "Neptune"
    };

    int pos1 = -1, pos2 = -1;
    for (int i = 0; i < 8 && (pos1 == -1 || pos2 == -1); ++i) {
        if (pos1 == -1 && planet1 == planets[i]) pos1 = i;
        if (pos2 == -1 && planet2 == planets[i]) pos2 = i;
    }

    if (pos1 == -1 || pos2 == -1) return {};

    if (pos1 > pos2) {
        int tmp = pos1;
        pos1 = pos2;
        pos2 = tmp;
    }

    vector<string> out;
    if (pos2 - pos1 > 1) {
        out.reserve(pos2 - pos1 - 1);
        for (int i = pos1 + 1; i < pos2; ++i) {
            out.emplace_back(planets[i]);
        }
    }
    return out;
}
