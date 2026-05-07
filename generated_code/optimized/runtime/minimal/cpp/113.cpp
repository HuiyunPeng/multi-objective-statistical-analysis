#include <vector>
#include <string>
using namespace std;

vector<string> odd_count(vector<string> lst) {
    static constexpr char p1[] = "the number of odd elements ";
    static constexpr char p2[] = "n the str";
    static constexpr char p3[] = "ng ";
    static constexpr char p4[] = " of the ";
    static constexpr char p5[] = "nput.";

    vector<string> out;
    out.reserve(lst.size());

    for (const string& str : lst) {
        int sum = 0;
        for (unsigned char c : str) {
            sum += (c >= '0' && c <= '9' && (c & 1));
        }

        string num = to_string(sum);
        string res;
        res.reserve((sizeof(p1) - 1) + (sizeof(p2) - 1) + (sizeof(p3) - 1) +
                    (sizeof(p4) - 1) + (sizeof(p5) - 1) + 4 * num.size());

        res.append(p1, sizeof(p1) - 1);
        res += num;
        res.append(p2, sizeof(p2) - 1);
        res += num;
        res.append(p3, sizeof(p3) - 1);
        res += num;
        res.append(p4, sizeof(p4) - 1);
        res += num;
        res.append(p5, sizeof(p5) - 1);

        out.emplace_back(std::move(res));
    }

    return out;
}
