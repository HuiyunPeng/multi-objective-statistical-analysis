#include <string>
#include <map>
using namespace std;

map<char,int> histogram(string test) {
    map<char,int> count;
    int maxCount = 0;

    for (char c : test) {
        if (c == ' ') continue;
        int newCount = ++count[c];
        if (newCount > maxCount) maxCount = newCount;
    }

    for (map<char, int>::iterator it = count.begin(); it != count.end(); ) {
        if (it->second != maxCount)
            count.erase(it++);
        else
            ++it;
    }

    return count;
}
