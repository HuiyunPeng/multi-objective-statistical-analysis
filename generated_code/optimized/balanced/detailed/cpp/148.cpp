#include <array>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> bf(string planet1, string planet2) {
    static const array<string, 8> planets = {
        "Mercury", "Venus", "Earth", "Mars",
        "Jupiter", "Saturn", "Uranus", "Neptune"
    };

    int pos1 = -1, pos2 = -1;
    for (int i = 0; i < 8 && (pos1 == -1 || pos2 == -1); ++i) {
        if (pos1 == -1 && planets[i] == planet1) pos1 = i;
        if (pos2 == -1 && planets[i] == planet2) pos2 = i;
    }

    if (pos1 == -1 || pos2 == -1) return {};
    if (pos1 > pos2) swap(pos1, pos2);

    return vector<string>(planets.begin() + pos1 + 1, planets.begin() + pos2);
}
