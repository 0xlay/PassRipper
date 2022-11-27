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
#include <fstream>
#include "Core/Bruteforce.h"
#include "Core/Password.h"
#include "Crypto/Hash/Utility.h"
#include "Utility/File.h"
#include "Argument.h"


int main(int argc, char** argv)
{
    static constexpr char kMessageInvalidArguments[] = \
    "Invalid arguments! Args: X:\\File.txt --alphabet=numerical/lowercase/uppercase/all --password-length=4 --threads=1"
    "[--log-password=X:\\Log.txt]";

    Core::Bruteforce::Config config;

    if (argc > 4)
    {
        config.alphabet = ParseAlphabet(argv[2]);
        if (config.alphabet.empty())
        {
            std::cout << kMessageInvalidArguments << std::endl;
            return -1;
        }

        config.passwordLength = ParsePasswordLength(argv[3]);
        if (!config.passwordLength)
        {
            std::cout << kMessageInvalidArguments << std::endl;
            return -1;
        }

        config.threadCount = ParseNumberOfThreads(argv[4]);
        if (!config.threadCount)
        {
            std::cout << kMessageInvalidArguments << std::endl;
            return -1;
        }

        if (argc > 5)
        {
            config.pathToLogFile = ParsePathToPasswordLog(argv[5]);
            if (config.pathToLogFile.empty())
            {
                std::cout << kMessageInvalidArguments << std::endl;
                return -1;
            }
        }
    }
    else if(argc > 2)
    {
        std::ifstream configFile(argv[2]);
        if (!configFile.is_open())
        {
            std::cout << kMessageInvalidArguments << std::endl;
            return -1;
        }
        try
        {
            nlohmann::json data = nlohmann::json::parse(configFile);
            config = Core::Bruteforce::ParseToConfig(data);
        }
        catch (nlohmann::json::exception const& ex)
        {
            std::cout << "Json exception: " << ex.what() << std::endl;
            return -1;
        }
    }
    else
    {
        std::cout << kMessageInvalidArguments << std::endl;
        return -1;
    }

    std::string fullPath = argv[1];

    std::string encryptedFile;
    if (!Utility::File::ReadData(fullPath, encryptedFile))
    {
        std::cout << "Failed to read data from encrypted file!" << std::endl;
        return -1;
    }

    std::string hash = Crypto::FetchHash(encryptedFile);

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
    catch(std::exception const& ex)
    {
        std::cout << "Standard exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown exception!!!" << std::endl;
    }

    return 0;
}
