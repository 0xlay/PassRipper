#include "gtest/gtest.h"
#include "Utility/String.h"
#include "Utility/String/Compare.h"
#include "Utility/String/Compare.cpp"


TEST(UtilityStringTest, InsensetiveCompare)
{
    constexpr char kLhs[] = "HElLO";
    constexpr char kRhs[] = "heLLo";

    ASSERT_TRUE(Utility::String::InsensetiveCompare(kLhs, kRhs));
}