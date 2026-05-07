#include <string>
#include <cstdlib>
#include <boost/any.hpp>

boost::any compare_one(boost::any a, boost::any b) {
    auto to_double = [](const boost::any& value) -> double {
        if (const int* pi = boost::any_cast<int>(&value)) {
            return static_cast<double>(*pi);
        }
        if (const double* pd = boost::any_cast<double>(&value)) {
            return *pd;
        }
        if (const std::string* ps = boost::any_cast<std::string>(&value)) {
            const std::string& s = *ps;
            if (s.find(',') == std::string::npos) {
                return std::strtod(s.c_str(), nullptr);
            }

            std::string tmp = s;
            for (char& ch : tmp) {
                if (ch == ',') ch = '.';
            }
            return std::strtod(tmp.c_str(), nullptr);
        }
        return 0.0;
    };

    const double numa = to_double(a);
    const double numb = to_double(b);

    if (numa == numb) return std::string("None");
    return (numa < numb) ? b : a;
}
