#include <vector>
#include <string>
using namespace std;

static inline int planetIndex(const string& p) {
    if (p.empty()) return -1;
    switch (p[0]) {
        case 'M':
            if (p == "Mercury") return 0;
            if (p == "Mars") return 3;
            break;
        case 'V':
            if (p == "Venus") return 1;
            break;
        case 'E':
            if (p == "Earth") return 2;
            break;
        case 'J':
            if (p == "Jupiter") return 4;
            break;
        case 'S':
            if (p == "Saturn") return 5;
            break;
        case 'U':
            if (p == "Uranus") return 6;
            break;
        case 'N':
            if (p == "Neptune") return 7;
            break;
    }
    return -1;
}

vector<string> bf(string planet1, string planet2) {
    static const string planets[] = {
        "Mercury", "Venus", "Earth", "Mars",
        "Jupiter", "Saturn", "Uranus", "Neptune"
    };

    int pos1 = planetIndex(planet1);
    int pos2 = planetIndex(planet2);

    if (pos1 == -1 || pos2 == -1) return {};
    if (pos1 > pos2) {
        int t = pos1;
        pos1 = pos2;
        pos2 = t;
    }
    if (pos2 - pos1 <= 1) return {};

    vector<string> out;
    out.reserve(pos2 - pos1 - 1);
    for (int i = pos1 + 1; i < pos2; ++i) {
        out.push_back(planets[i]);
    }
    return out;
}
