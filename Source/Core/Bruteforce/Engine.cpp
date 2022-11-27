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
// File: Engine.cpp
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Core::Bruteforce
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <thread>
#include <algorithm>
#include <fstream>
#include "Engine.h"
#include "Core/Password/Generate.h"
#include "Crypto/Cipher.h"
#include "Crypto/Cipher/AES_128_CBC.h"
#include "Crypto/Hash.h"
#include "Crypto/Hash/SHA256.h"
#include "Utility/String.h"


namespace Core::Bruteforce
{

    Engine::Engine(Config config)
        : m_config(std::move(config)), m_isFound(false)
    {
        if (m_config.threadCount > m_config.passwordLength)
        {
            m_config.threadCount = m_config.passwordLength;
        }
        if (m_config.threadCount == 0)
        {
            m_config.threadCount = 1;
        }
    }


    bool Engine::run()
    {
        bool status = true;
        std::size_t step = m_config.passwordLength / m_config.threadCount;
        std::vector<std::thread> threads;

        try
        {
            for (std::size_t i = 0; i < m_config.passwordLength; i += step)
            {
                std::size_t currentAttempts = Password::CalculateAttempts(m_config.alphabet.length(), i + step);
                std::size_t previousAttempts = Password::CalculateAttempts(m_config.alphabet.length(), i);

                Core::Password::Config config
                {
                    .numberOfPassword = currentAttempts - previousAttempts,
                    .alphabet = m_config.alphabet,
                    .range = {i, i + step}
                };

                threads.emplace_back(std::thread(&Engine::brute, this, std::move(config)));
            }

            for (auto&& thread : threads)
            {
                thread.join();
            }
        }
        catch(std::exception const&)
        {
            status = false;
        }

        return status;
    }


    void Engine::setEncryptedText(std::string encryptedText) noexcept
    {
        m_encryptedText = std::move(encryptedText);
    }


    std::string Engine::fetchDecryptedText() noexcept
    {
        return std::move(m_decryptedText);
    }


    void Engine::setHash(std::string hash) noexcept
    {
        m_hash = std::move(hash);
    }


    std::string Engine::getPassword() const
    {
        return m_password;
    }


    void Engine::reset(Config config) noexcept
    {
        m_config = std::move(config);
    }


    void Engine::brute(Core::Password::Config config)
    {
        Crypto::Cipher cipher(std::make_unique<Crypto::AES_128_CBC>(""));
        Crypto::Hash hash(std::make_unique<Crypto::SHA256>());

        std::vector<std::string> passwords = Password::Generate(config);

        for (auto it = passwords.begin(); it != passwords.end(); ++it)
        {
            if (m_isFound)
            {
                savePasswords(passwords.begin(), it);
                return;
            }

            cipher.resetPassword(*it);
            
            std::string decryptedText;
            if (cipher.decrypt(m_encryptedText, decryptedText))
            {
                if(hash.generate(decryptedText))
                {
                    if (Utility::String::InsensetiveCompare(hash.toHexString(), m_hash))
                    {
                        m_isFound = true;
                        savePasswords(passwords.begin(), it);
                        m_decryptedText = std::move(decryptedText);
                        m_password = *it;
                        return;
                    }
                }
            }
        }

        savePasswords(passwords.begin(), passwords.end());
    }


    void Engine::savePasswords(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end)
    {
        std::scoped_lock lock(m_lockerSaveToFile);
        if (!m_config.pathToLogFile.empty())
        {
            std::ofstream file(m_config.pathToLogFile, std::ios::app);
            if (file.is_open())
            {
                std::copy(std::move(begin), std::move(end), std::ostream_iterator<std::string>(file, "\n"));
            }
        }
    }

} // Core::Bruteforce
