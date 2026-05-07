#include <vector>

int next_smallest(std::vector<int> lst) {
    bool has_min1 = false, has_min2 = false;
    int min1 = 0, min2 = 0;

    for (int x : lst) {
        if (!has_min1 || x < min1) {
            if (has_min1 && x != min1) {
                min2 = min1;
                has_min2 = true;
            }
            min1 = x;
            has_min1 = true;
        } else if (x != min1 && (!has_min2 || x < min2)) {
            min2 = x;
            has_min2 = true;
        }
    }

    return has_min2 ? min2 : -1;
}
