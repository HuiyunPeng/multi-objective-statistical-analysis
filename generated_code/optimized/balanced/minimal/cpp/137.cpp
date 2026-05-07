#include <boost/any.hpp>
#include <string>
#include <cstdlib>

static inline double any_to_double(const boost::any& value) {
    if (const int* pi = boost::any_cast<int>(&value)) {
        return static_cast<double>(*pi);
    }
    if (const double* pd = boost::any_cast<double>(&value)) {
        return *pd;
    }
    if (const std::string* ps = boost::any_cast<std::string>(&value)) {
        const std::string& s = *ps;
        const std::size_t pos = s.find(',');
        if (pos == std::string::npos) {
            return std::strtod(s.c_str(), nullptr);
        }

        std::string normalized = s;
        for (std::size_t i = pos; i < normalized.size(); ++i) {
            if (normalized[i] == ',') {
                normalized[i] = '.';
            }
        }
        return std::strtod(normalized.c_str(), nullptr);
    }
    return 0.0;
}

boost::any compare_one(boost::any a, boost::any b) {
    const double numa = any_to_double(a);
    const double numb = any_to_double(b);

    if (numa == numb) {
        return std::string("None");
    }
    return (numa < numb) ? b : a;
}
