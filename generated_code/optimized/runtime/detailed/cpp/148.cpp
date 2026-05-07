#include <vector>
#include <string>
using namespace std;

vector<string> bf(string planet1, string planet2) {
    static const string planets[] = {
        "Mercury", "Venus", "Earth", "Mars",
        "Jupiter", "Saturn", "Uranus", "Neptune"
    };

    auto getPos = [](const string& p) -> int {
        if (p == "Mercury") return 0;
        if (p == "Venus")   return 1;
        if (p == "Earth")   return 2;
        if (p == "Mars")    return 3;
        if (p == "Jupiter") return 4;
        if (p == "Saturn")  return 5;
        if (p == "Uranus")  return 6;
        if (p == "Neptune") return 7;
        return -1;
    };

    int pos1 = getPos(planet1);
    int pos2 = getPos(planet2);

    if (pos1 == -1 || pos2 == -1) return {};

    if (pos1 > pos2) {
        int t = pos1;
        pos1 = pos2;
        pos2 = t;
    }

    vector<string> out;
    int count = pos2 - pos1 - 1;
    if (count <= 0) return out;

    out.reserve(count);
    for (int i = pos1 + 1; i < pos2; ++i) {
        out.push_back(planets[i]);
    }
    return out;
}
