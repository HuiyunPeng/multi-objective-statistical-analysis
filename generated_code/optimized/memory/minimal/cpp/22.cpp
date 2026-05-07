#include <vector>
#include <list>
#include <boost/any.hpp>

typedef std::list<boost::any> list_any;
using namespace std;

vector<int> filter_integers(list_any values) {
    vector<int> out;
    size_t count = 0;

    for (const auto& value : values) {
        if (boost::any_cast<int>(&value)) {
            ++count;
        }
    }

    out.reserve(count);

    for (const auto& value : values) {
        if (const int* p = boost::any_cast<int>(&value)) {
            out.push_back(*p);
        }
    }

    return out;
}
