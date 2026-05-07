#include <string>
#include <boost/any.hpp>
#include <cstdlib>

using namespace std;

static inline double any_to_double(const boost::any& v) {
    const std::type_info& t = v.type();

    if (t == typeid(int)) {
        return static_cast<double>(boost::any_cast<int>(v));
    }
    if (t == typeid(double)) {
        return boost::any_cast<double>(v);
    }
    if (t == typeid(string)) {
        const string& s = boost::any_cast<const string&>(v);

        size_t comma_pos = s.find(',');
        if (comma_pos == string::npos) {
            return atof(s.c_str());
        }

        string tmp = s;
        do {
            tmp[comma_pos] = '.';
            comma_pos = tmp.find(',', comma_pos + 1);
        } while (comma_pos != string::npos);

        return atof(tmp.c_str());
    }

    return 0.0;
}

boost::any compare_one(boost::any a, boost::any b) {
    const double numa = any_to_double(a);
    const double numb = any_to_double(b);

    if (numa == numb) return string("None");
    return (numa < numb) ? b : a;
}
