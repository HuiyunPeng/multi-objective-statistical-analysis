#include <string>
#include <cstdlib>
#include <boost/any.hpp>

static double any_to_double(const boost::any& value) {
    if (const std::string* s = boost::any_cast<std::string>(&value)) {
        if (s->find(',') == std::string::npos) {
            return std::atof(s->c_str());
        }

        std::string normalized(*s);
        for (std::string::size_type i = 0; i < normalized.size(); ++i) {
            if (normalized[i] == ',') {
                normalized[i] = '.';
            }
        }
        return std::atof(normalized.c_str());
    }

    if (const int* i = boost::any_cast<int>(&value)) {
        return static_cast<double>(*i);
    }

    if (const double* d = boost::any_cast<double>(&value)) {
        return *d;
    }

    return 0.0;
}

boost::any compare_one(boost::any a, boost::any b) {
    const double numa = any_to_double(a);
    const double numb = any_to_double(b);

    if (numa == numb || (!(numa < numb) && !(numa > numb))) {
        return std::string("None");
    }
    if (numa < numb) {
        return b;
    }
    return a;
}
