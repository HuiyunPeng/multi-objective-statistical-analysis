#include <vector>
#include <list>
#include <boost/any.hpp>

typedef std::list<boost::any> list_any;
using namespace std;

vector<int> filter_integers(list_any values) {
    vector<int> out;
    out.reserve(values.size());

    for (const auto& v : values) {
        if (const int* p = boost::any_cast<int>(&v)) {
            out.push_back(*p);
        }
    }

    return out;
}
