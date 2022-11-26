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
// File: Cipher.h
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Crypto
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <string_view>
#include <memory>


namespace Crypto
{
    struct ICipher;

    class Cipher final
    {
    public:
        explicit Cipher(std::unique_ptr<ICipher> cipher);

        [[nodiscard]] bool encrypt(std::string_view plainText, std::string& cipherText);
        [[nodiscard]] bool decrypt(std::string_view cipherText, std::string& plainText);

        void resetPassword(std::string_view password) noexcept;

    private:
        std::unique_ptr<ICipher> m_cipher;
    };

} // Crypto