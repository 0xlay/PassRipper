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
// File: Main.cpp
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Core/Bruteforce.h"
#include "Core/Password.h"
#include "Crypto/Hash/Utility.h"
#include "Utility/File.h"


int main(int argc, char** argv)
{
    static constexpr char kMessageInvalidArguments[] = \
    "Invalid arguments! Args: X:\\File.txt --alphabet=numerical/lowercase/uppercase/all --password-length=4 --threads=1"
    "[--log-password=X:\\Log.txt]";

    if (argc < 5)
    {
        std::cout << kMessageInvalidArguments << std::endl;
        return -1;
    }

    std::string fullPath = argv[1];

    std::string alphabet;
    if (std::strcmp(argv[2], "--alphabet=numerical") == 0)
    {
        alphabet = Core::Password::kNumericAlphabet;
    }
    else if (std::strcmp(argv[2], "--alphabet=lowercase") == 0)
    {
        alphabet = Core::Password::kLowerCaseAlphabet;
    }
    else if (std::strcmp(argv[2], "--alphabet=uppercase") == 0)
    {
        alphabet = Core::Password::kUpperCaseAlphabet;
    }
    else if(std::strcmp(argv[2], "--alphabet=all") == 0)
    {
        alphabet = Core::Password::kNumericAlphabet;
        alphabet += Core::Password::kLowerCaseAlphabet;
        alphabet += Core::Password::kUpperCaseAlphabet;
    }
    else
    {
        std::cout << kMessageInvalidArguments << std::endl;
        return -1;

    }

    std::size_t passwordLength = 0;
    static constexpr char kArgumentPasswordLength[] = "--password-length=";
    if (std::strncmp(argv[3], kArgumentPasswordLength, sizeof(kArgumentPasswordLength) - 1) == 0)
    {
        passwordLength = std::stoll(std::string(argv[3] + sizeof(kArgumentPasswordLength) - 1));
    }
    else
    {
        std::cout << kMessageInvalidArguments << std::endl;
        return -1;
    }

    std::size_t threads = 0;
    static constexpr char kArgumentThreads[] = "--threads=";
    if (std::strncmp(argv[4], kArgumentThreads, sizeof(kArgumentThreads) - 1) == 0)
    {
        threads = std::stoll(std::string(argv[4] + sizeof(kArgumentThreads) - 1));
    }
    else
    {
        std::cout << kMessageInvalidArguments << std::endl;
        return -1;
    }

    std::string pathToLogFile;
    static constexpr char kArgumentPathToLogFile[] = "--log-password=";
    if (argc > 5)
    {
        if (std::strncmp(argv[5], kArgumentPathToLogFile, sizeof(kArgumentPathToLogFile) - 1) == 0)
        {
            pathToLogFile = std::string(argv[5] + sizeof(kArgumentPathToLogFile) - 1);
        }
    }

    std::string encryptedFile;
    if (!Utility::File::ReadData(fullPath, encryptedFile))
    {
        std::cout << "Failed to read data from encrypted file!" << std::endl;
        return -1;
    }

    std::string hash = Crypto::FetchHash(encryptedFile);

    Core::Bruteforce::Config config {
        .alphabet = std::move(alphabet),
        .passwordLength = passwordLength,
        .threadCount = threads,
        .pathToLogFile = std::move(pathToLogFile)
    };

    Core::Bruteforce::Engine engine(std::move(config));
    engine.setHash(std::move(hash));
    engine.setEncryptedText(std::move(encryptedFile));

    try
    {
        if (engine.run())
        {
            if (std::string password = engine.getPassword(); password.empty())
            {
                std::cout << "Your password not found!" << std::endl;
            }
            else
            {
                std::cout << "Your password: " << password << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to brute password!" << std::endl;
        }
    }
    catch(std::bad_alloc const& ex)
    {
        std::cout << "Not enough memory! Standard alloc exception: " << ex.what() << std::endl;
    }
    catch(std::exception const ex)
    {
        std::cout << "Standard exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception!!!" << std::endl;
    }

    return 0;
}
