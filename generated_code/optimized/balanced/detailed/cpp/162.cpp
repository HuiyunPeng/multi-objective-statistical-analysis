#include <string>
#include <openssl/md5.h>

std::string string_to_md5(std::string text) {
    if (text.empty()) return "None";

    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(text.data()), text.size(), digest);

    static const char hex[] = "0123456789abcdef";
    std::string out(2 * MD5_DIGEST_LENGTH, '\0');

    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        const unsigned char b = digest[i];
        out[2 * i]     = hex[b >> 4];
        out[2 * i + 1] = hex[b & 0x0F];
    }

    return out;
}
