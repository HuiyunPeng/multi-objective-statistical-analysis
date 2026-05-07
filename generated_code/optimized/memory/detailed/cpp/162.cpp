#include <string>
#include <openssl/md5.h>

using namespace std;

string string_to_md5(string text) {
    if (text.empty()) return "None";

    unsigned char md[MD5_DIGEST_LENGTH];
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c, text.data(), text.size());
    MD5_Final(md, &c);

    static const char hex[] = "0123456789abcdef";
    string out_str;
    out_str.resize(MD5_DIGEST_LENGTH * 2);

    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        const unsigned char b = md[i];
        out_str[2 * i] = hex[b >> 4];
        out_str[2 * i + 1] = hex[b & 0x0F];
    }

    return out_str;
}
