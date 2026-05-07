#include <vector>
#include <list>
#include <boost/any.hpp>

typedef std::list<boost::any> list_any;

std::vector<int> filter_integers(list_any values) {
    std::size_t count = 0;
    for (list_any::const_iterator it = values.begin(); it != values.end(); ++it) {
        if (it->type() == typeid(int)) {
            ++count;
        }
    }

    std::vector<int> out;
    out.reserve(count);

    for (list_any::const_iterator it = values.begin(); it != values.end(); ++it) {
        if (it->type() == typeid(int)) {
            out.push_back(boost::any_cast<int>(*it));
        }
    }

    return out;
}
