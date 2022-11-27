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
// File: Engine.h
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Core::Bruteforce
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include <string>
#include <mutex>
#include "Config.h"


namespace Core::Password
{
    struct Config;
}


namespace Core::Bruteforce
{

    class Engine final
    {
    public:
        explicit Engine(Config config);

        [[nodiscard]] bool run();

        void setEncryptedText(std::string encryptedText) noexcept;

        [[nodiscard]] std::string fetchDecryptedText() noexcept;

        void setHash(std::string hash) noexcept;

        [[nodiscard]] std::string getPassword() const;

        void reset(Config config) noexcept;

    private:
        void brute(Core::Password::Config config);
        void savePasswords(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end);

    private:
        Config m_config;
        bool m_isFound;
        std::string m_encryptedText;
        std::string m_hash;
        std::string m_decryptedText;
        std::string m_password;
        std::mutex m_lockerSaveToFile;
    };

} // Core::Bruteforce
