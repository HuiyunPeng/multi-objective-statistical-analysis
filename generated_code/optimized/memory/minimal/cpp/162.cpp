#include <string>
#include <openssl/md5.h>

std::string string_to_md5(std::string text) {
    if (text.empty()) return "None";

    unsigned char md[MD5_DIGEST_LENGTH];
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c, text.data(), text.size());
    MD5_Final(md, &c);

    static const char hex[] = "0123456789abcdef";
    char out[MD5_DIGEST_LENGTH * 2];
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        out[i * 2] = hex[md[i] >> 4];
        out[i * 2 + 1] = hex[md[i] & 0x0F];
    }

    return std::string(out, sizeof(out));
}
