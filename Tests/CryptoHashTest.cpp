#include "gtest/gtest.h"
#include "Crypto/Hash.h"
#include "Crypto/Hash.cpp"
#include "Crypto/Hash/SHA256.h"
#include "Crypto/Hash/SHA256.cpp"


TEST(CryptoHashTest, SHA256)
{
    constexpr char kSource[] = "hello world";
    constexpr char kTarget[] = "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9";

    std::string hashAsHexString;
    Crypto::Hash hash = Crypto::Hash(std::make_unique<Crypto::SHA256>());

    ASSERT_TRUE(hash.generate(kSource));
    ASSERT_EQ(kTarget, hash.toHexString());
}
