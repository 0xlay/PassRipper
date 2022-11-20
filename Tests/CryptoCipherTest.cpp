#include "gtest/gtest.h"
#include "Crypto/Cipher.h"
#include "Crypto/Cipher.cpp"
#include "Crypto/Cipher/AES_128_CBC.h"
#include "Crypto/Cipher/AES_128_CBC.cpp"


TEST(CryptoCipherTest, AES_128_CBC)
{
    constexpr char kPassword[] = "1234567890";
    constexpr char kSource[] = "hello world";

    std::string sourceEncrypted;
    std::string sourceDecrypted;
    Crypto::Cipher cipher = Crypto::Cipher(std::make_unique<Crypto::AES_128_CBC>(kPassword));

    ASSERT_TRUE(cipher.encrypt(kSource, sourceEncrypted));
    ASSERT_TRUE(cipher.decrypt(sourceEncrypted, sourceDecrypted));

    ASSERT_EQ(kSource, sourceDecrypted);
}
