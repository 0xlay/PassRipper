#include "gtest/gtest.h"
#include "Crypto/Hash.h"
#include "Crypto/Hash.cpp"
#include "Crypto/Hash/SHA256.h"
#include "Crypto/Hash/SHA256.cpp"
#include "Utility/String/Convert.h"
#include "Utility/String/Convert.cpp"


TEST(CryptoHashTest, SHA256SingleIteration)
{
    static constexpr char kSource[] = "hello world";
    static constexpr char kTarget[] = "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9";

    std::string hashAsHexString;
    Crypto::Hash hash = Crypto::Hash(std::make_unique<Crypto::SHA256>());

    ASSERT_TRUE(hash.generate(kSource));
    ASSERT_EQ(kTarget, hash.toHexString());
}

TEST(CryptoHashTest, SHA256MultipleIteration)
{
    static constexpr char kFirstSource[] = "hello world";
    static constexpr char kFirstTarget[] = "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9";
    static constexpr char kSecondSource[] = "Hello world my friend! I'm a programmer";
    static constexpr char kSecondTarget[] = "a0984e80b1a7e59a36ec9f587bfd06d15a130bdee9ea45d58a2156778b22f6f7";

    std::string hashAsHexString;
    Crypto::Hash hash = Crypto::Hash(std::make_unique<Crypto::SHA256>());

    ASSERT_TRUE(hash.generate(kFirstSource));
    ASSERT_EQ(kFirstTarget, hash.toHexString());

    ASSERT_TRUE(hash.generate(kSecondSource));
    ASSERT_EQ(kSecondTarget, hash.toHexString());
}