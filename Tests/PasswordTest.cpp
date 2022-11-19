#include "gtest/gtest.h"
#include "Core/Password.h"
#include "Core/Password/Generate.cpp"

bool operator==(std::vector<std::string> const& lhs, std::vector<std::string> const& rhs);


TEST(PssswordTest, GeneratePasswordForLowerCaseAlphabet)
{
    std::vector<std::string> sourcePasswords
    {
        "a",  "b",  "c",  "d", "aa", "ba", "ca", "da", "ab", "bb", "cb", "db",
        "ac", "bc", "cc", "dc", "ad", "bd", "cd", "dd"
    };

    Core::Password::Config config {
        .numberOfPassword = 20,
        .alphabet = "abcd",
        .range = {0, 2}
    };

    std::vector<std::string> passwords = Core::Password::Generate(config);

    ASSERT_EQ(sourcePasswords, passwords);
}


TEST(PssswordTest, GeneratePasswordForUpperCaseAlphabet)
{
    std::vector<std::string> sourcePasswords
    {
        "A",  "B",  "C",  "D", "AA", "BA", "CA", "DA", "AB", "BB", "CB", "DB",
        "AC", "BC", "CC", "DC", "AD", "BD", "CD", "DD"
    };

    Core::Password::Config config {
        .numberOfPassword = 20,
        .alphabet = "ABCD",
        .range = {0, 2}
    };

    std::vector<std::string> passwords = Core::Password::Generate(config);

    ASSERT_EQ(sourcePasswords, passwords);
}


TEST(PssswordTest, GeneratePasswordForNumericAlphabet)
{
    std::vector<std::string> sourcePasswords
    {
        "0",  "1",  "2",  "3",
        "00", "10", "20", "30",
        "01", "11", "21", "31",
        "02", "12", "22", "32",
        "03", "13", "23", "33"
    };

    Core::Password::Config config {
        .numberOfPassword = 20,
        .alphabet = "0123",
        .range = {0, 2}
    };

    std::vector<std::string> passwords = Core::Password::Generate(config);

    ASSERT_EQ(sourcePasswords, passwords);
}


bool operator==(std::vector<std::string> const& lhs, std::vector<std::string> const& rhs)
{
    bool status = true;

    if (lhs.size() == rhs.size())
    {
        for(std::size_t i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
            {
                status = false;
                break;
            }
        }
    }
    else
    {
        status = false;
    }

    return status;
}