#include <iostream>
#include "openssl/evp.h"

int main() {
    OpenSSL_add_all_algorithms();
    const EVP_MD* dgst = EVP_get_digestbyname("md5");
    if (dgst == nullptr)
        std::cout << "empty" << std::endl;
    else
        std::cout << "Hello, World!" << std::endl;
    return 0;
}
