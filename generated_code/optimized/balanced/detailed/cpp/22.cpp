#include <vector>
#include <list>
#include <boost/any.hpp>

typedef std::list<boost::any> list_any;

std::vector<int> filter_integers(list_any values) {
    std::vector<int> out;
    out.reserve(values.size());

    for (const auto& item : values) {
        if (const int* p = boost::any_cast<int>(&item)) {
            out.push_back(*p);
        }
    }

    return out;
}
