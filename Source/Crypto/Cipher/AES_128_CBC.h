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
// File: AES_128_CBC.h
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Crypto
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "ICipher.h"

struct evp_cipher_ctx_st;


namespace Crypto
{

    class AES_128_CBC : public ICipher
    {
        static constexpr std::size_t kIterationCount = 1;

    public:
        explicit AES_128_CBC(std::string_view password);
        ~AES_128_CBC() noexcept override;

        AES_128_CBC(AES_128_CBC&& rhs) noexcept;
        AES_128_CBC& operator=(AES_128_CBC&& rhs) noexcept;

        [[nodiscard]] bool encrypt(std::string_view plainText, std::string &cipherText) noexcept override;
        [[nodiscard]] bool decrypt(std::string_view cipherText, std::string &plainText) noexcept override;

    private:
        [[nodiscard]] bool encryptInit();
        [[nodiscard]] bool encryptUpdate(std::string_view plainText, std::string &cipherText);
        [[nodiscard]] bool encryptFinal(std::string& cipherText);

        [[nodiscard]] bool decryptInit();
        [[nodiscard]] bool decryptUpdate(std::string_view cipherText, std::string& plainText);
        [[nodiscard]] bool decryptFinal(std::string& plainText);

    private:
        evp_cipher_ctx_st* m_ctx;
        int m_textSizeAfterUpdate;

        std::string m_key;
        std::string m_iv;

        bool m_isInitialized;
    };

} // Crypto