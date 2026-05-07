#include <string>
#include <cstdlib>
#include <boost/any.hpp>

static double any_to_double(const boost::any& value) {
    if (value.type() == typeid(int)) {
        return static_cast<double>(boost::any_cast<int>(value));
    }
    if (value.type() == typeid(double)) {
        return boost::any_cast<double>(value);
    }
    if (value.type() == typeid(std::string)) {
        const std::string& s = boost::any_cast<const std::string&>(value);
        if (s.find(',') == std::string::npos) {
            return std::strtod(s.c_str(), NULL);
        }

        std::string tmp(s);
        for (size_t i = 0; i < tmp.size(); ++i) {
            if (tmp[i] == ',') tmp[i] = '.';
        }
        return std::strtod(tmp.c_str(), NULL);
    }
    return 0.0;
}

boost::any compare_one(boost::any a, boost::any b) {
    const double numa = any_to_double(a);
    const double numb = any_to_double(b);

    if (numa == numb) return std::string("None");
    return (numa < numb) ? b : a;
}
