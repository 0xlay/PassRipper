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

    private:
        Config m_config;
        std::string m_encryptedText;
        std::string m_hash;
        std::string m_decryptedText;
        std::string m_password;
    };

} // Core::Bruteforce
