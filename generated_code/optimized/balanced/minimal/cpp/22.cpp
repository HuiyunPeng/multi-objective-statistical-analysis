#include <vector>
#include <list>
#include <boost/any.hpp>

typedef std::list<boost::any> list_any;

std::vector<int> filter_integers(list_any values) {
    std::vector<int> out;
    for (const boost::any& value : values) {
        if (const int* p = boost::any_cast<int>(&value)) {
            out.push_back(*p);
        }
    }
    return out;
}
