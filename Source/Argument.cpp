////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      _______                               _______   __
//    /       \                             /       \ /  |
//    $$$$$$$  | ______    _______  _______ $$$$$$$  |$$/   ______    ______    ______    ______
//    $$ |__$$ |/      \  /       |/       |$$ |__$$ |/  | /      \  /      \  /      \  /      \
//    $$    $$/ $$$$$$  |/$$$$$$$//$$$$$$$/ $$    $$< $$ |/$$$$$$  |/$$$$$$  |/$$$$$$  |/$$$$$$  |
//    $$$$$$$/  /    $$ |$$      \$$      \ $$$$$$$  |$$ |$$ |  $$ |$$ |  $$ |$$    $$ |$$ |  $$/
//    $$ |     /$$$$$$$ | $$$$$$  |$$$$$$  |$$ |  $$ |$$ |$$ |__$$ |$$ |__$$ |$$$$$$$$/ $$ |
//    $$ |     $$    $$ |/     $$//     $$/ $$ |  $$ |$$ |$$    $$/ $$    $$/ $$       |$$ |
//    $$/       $$$$$$$/ $$$$$$$/ $$$$$$$/  $$/   $$/ $$/ $$$$$$$/  $$$$$$$/   $$$$$$$/ $$/
//                                                        $$ |      $$ |
//                                                        $$ |      $$ |
//                                                        $$/       $$/
//
// Copyright Ⓒ 0xlay. All rights reserved.
//
// This source file is licensed under the terms of MIT license.
// For details, please read the LICENSE file.
//
// File: Argument.cpp
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Core/Password.h"
#include "Argument.h"


std::string ParseAlphabet(std::string_view argument)
{
    std::string alphabet;

    if (std::strcmp(argument.data(), "--alphabet=numerical") == 0)
    {
        alphabet = Core::Password::kNumericAlphabet;
    }
    else if (std::strcmp(argument.data(), "--alphabet=lowercase") == 0)
    {
        alphabet = Core::Password::kLowerCaseAlphabet;
    }
    else if (std::strcmp(argument.data(), "--alphabet=uppercase") == 0)
    {
        alphabet = Core::Password::kUpperCaseAlphabet;
    }
    else if(std::strcmp(argument.data(), "--alphabet=all") == 0)
    {
        alphabet = Core::Password::kNumericAlphabet;
        alphabet += Core::Password::kLowerCaseAlphabet;
        alphabet += Core::Password::kUpperCaseAlphabet;
    }

    return alphabet;
}


std::size_t ParsePasswordLength(std::string_view argument)
{
    static constexpr char kArgumentPasswordLength[] = "--password-length=";
    std::size_t passwordLength = 0;
    if (std::strncmp(argument.data(), kArgumentPasswordLength, sizeof(kArgumentPasswordLength) - 1) == 0)
    {
        passwordLength = std::stoll(std::string(argument.data() + sizeof(kArgumentPasswordLength) - 1));
    }
    return passwordLength;
}


std::size_t ParseNumberOfThreads(std::string_view argument)
{
    std::size_t threads = 0;
    static constexpr char kArgumentThreads[] = "--threads=";
    if (std::strncmp(argument.data(), kArgumentThreads, sizeof(kArgumentThreads) - 1) == 0)
    {
        threads = std::stoll(std::string(argument.data() + sizeof(kArgumentThreads) - 1));
    }
    return threads;
}


std::string ParsePathToPasswordLog(std::string_view argument)
{
    std::string pathToLogFile;
    static constexpr char kArgumentPathToLogFile[] = "--log-password=";
    if (std::strncmp(argument.data(), kArgumentPathToLogFile, sizeof(kArgumentPathToLogFile) - 1) == 0)
    {
        pathToLogFile = std::string(argument.data() + sizeof(kArgumentPathToLogFile) - 1);
    }
    return pathToLogFile;
}
