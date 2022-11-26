#include "gtest/gtest.h"
#include "Core/Bruteforce.h"
#include "Core/Bruteforce/Engine.cpp"


struct BruteforceTest : public testing::Test
{
    static constexpr char kText[] = "Hello world my friend! I'm a programmer";
    static constexpr char kHashForOriginalText[] = "a0984e80b1a7e59a36ec9f587bfd06d15a130bdee9ea45d58a2156778b22f6f7";
    static constexpr char kPassword[] = "pass";

    static inline std::string m_encryptedText;
    static inline Core::Bruteforce::Engine* m_engine;

    static void SetUpTestCase()
    {
        Crypto::Cipher cipher = Crypto::Cipher(std::make_unique<Crypto::AES_128_CBC>(kPassword));
        ASSERT_TRUE(cipher.encrypt(kText, m_encryptedText));

        Core::Bruteforce::Config config {
            .alphabet = Core::Password::kLowerCaseAlphabet,
            .passwordLength = 4,
            .threadCount = 4
        };

        m_engine = new Core::Bruteforce::Engine(config);
    }

    static void TearDownTestCase()
    {
        delete m_engine;
    }

};


TEST_F(BruteforceTest, RunEnigneForDecryptText)
{
    m_engine->setEncryptedText(m_encryptedText);
    m_engine->setHash(kHashForOriginalText);

    ASSERT_TRUE(m_engine->run());
}


TEST_F(BruteforceTest, FetchDecryptionText)
{
    std::string decryptedText = m_engine->fetchDecryptedText();

    ASSERT_EQ(kText, decryptedText);
}