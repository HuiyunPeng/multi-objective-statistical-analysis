#include <string>
#include <algorithm>
#include <cstdlib>
#include <boost/any.hpp>

static inline double any_to_double(const boost::any& value) {
    const std::type_info& t = value.type();

    if (t == typeid(int)) {
        return static_cast<double>(boost::any_cast<int>(value));
    }
    if (t == typeid(double)) {
        return boost::any_cast<double>(value);
    }
    if (t == typeid(std::string)) {
        std::string s = boost::any_cast<std::string>(value);
        std::replace(s.begin(), s.end(), ',', '.');
        return std::strtod(s.c_str(), 0);
    }

    return 0.0;
}

boost::any compare_one(boost::any a, boost::any b) {
    const double numa = any_to_double(a);
    const double numb = any_to_double(b);

    if (numa == numb) return std::string("None");
    return (numa < numb) ? b : a;
}
