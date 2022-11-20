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
// File: AES_128_CBC.cpp
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Crypto
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include "AES_128_CBC.h"


namespace Crypto
{

    AES_128_CBC::AES_128_CBC(std::string_view password)
        : m_ctx(nullptr), m_textSizeAfterUpdate(0), m_isInitialized(false)
    {
        m_key.resize(EVP_MAX_KEY_LENGTH);
        m_key.resize(EVP_MAX_IV_LENGTH);

        m_isInitialized = EVP_BytesToKey(
            EVP_aes_128_cbc(), EVP_md5(), nullptr,
            reinterpret_cast<const std::uint8_t*>(password.data()), password.size(),
            kIterationCount,
            reinterpret_cast<std::uint8_t*>(m_key.data()), reinterpret_cast<std::uint8_t*>(m_iv.data())
        );

        if (m_isInitialized)
        {
            m_ctx = EVP_CIPHER_CTX_new();
            if (!m_ctx)
            {
                m_isInitialized = false;
            }
        }
    }


    AES_128_CBC::~AES_128_CBC() noexcept
    {
        if (m_ctx)
        {
            EVP_CIPHER_CTX_free(m_ctx);
        }
    }


    AES_128_CBC::AES_128_CBC(AES_128_CBC &&rhs) noexcept
        : m_ctx(nullptr), m_textSizeAfterUpdate(0), m_isInitialized(false)
    {
        std::swap(m_ctx, rhs.m_ctx);
        std::swap(m_textSizeAfterUpdate, rhs.m_textSizeAfterUpdate);
        std::swap(m_key, rhs.m_key);
        std::swap(m_iv, rhs.m_iv);
        std::swap(m_isInitialized, rhs.m_isInitialized);
    }


    AES_128_CBC& AES_128_CBC::operator=(AES_128_CBC &&rhs) noexcept
    {
        if (this != &rhs)
        {
            std::swap(m_ctx, rhs.m_ctx);
            std::swap(m_textSizeAfterUpdate, rhs.m_textSizeAfterUpdate);
            std::swap(m_key, rhs.m_key);
            std::swap(m_iv, rhs.m_iv);
            std::swap(m_isInitialized, rhs.m_isInitialized);
        }
        return *this;
    }


    bool AES_128_CBC::encrypt(std::string_view plainText, std::string &cipherText) noexcept
    {
        bool status = false;

        if (m_isInitialized)
        {
            try
            {
                if (encryptInit())
                {
                    if (encryptUpdate(plainText, cipherText))
                    {
                        status = encryptFinal(cipherText);
                    }
                }
            }
            catch(std::bad_alloc const&)
            {
                status = false;
            }
        }

        return status;
    }


    bool AES_128_CBC::decrypt(std::string_view cipherText, std::string &plainText) noexcept
    {
        bool status = false;

        if (m_isInitialized)
        {
            try
            {
                if(decryptInit())
                {
                    if (decryptUpdate(cipherText, plainText))
                    {
                        status = decryptFinal(plainText);
                    }
                }
            }
            catch(std::bad_alloc const&)
            {
                status = false;
            }
        }

        return status;
    }


    bool AES_128_CBC::encryptInit()
    {
        assert(m_ctx);
        return EVP_EncryptInit_ex(
            m_ctx, EVP_aes_128_cbc(), nullptr,
            reinterpret_cast<std::uint8_t*>(m_key.data()), reinterpret_cast<std::uint8_t*>(m_iv.data())
        );
    }


    bool AES_128_CBC::encryptUpdate(std::string_view plainText, std::string &cipherText)
    {
        assert(m_ctx);
        cipherText.resize(plainText.size() + AES_BLOCK_SIZE);
        return EVP_EncryptUpdate(
            m_ctx,
            reinterpret_cast<std::uint8_t*>(cipherText.data()), &m_textSizeAfterUpdate,
            reinterpret_cast<const std::uint8_t*>(plainText.data()), static_cast<int>(plainText.size())
        );
    }


    bool AES_128_CBC::encryptFinal(std::string& cipherText)
    {
        assert(m_ctx);
        bool status = false;
        int lastPartLength = 0;

        status = EVP_EncryptFinal_ex(
            m_ctx,
            reinterpret_cast<std::uint8_t*>(cipherText.data()) + m_textSizeAfterUpdate, &lastPartLength
        );
        if (status)
        {
            cipherText.resize(m_textSizeAfterUpdate + lastPartLength);
        }

        return status;
    }


    bool AES_128_CBC::decryptInit()
    {
        assert(m_ctx);
        return EVP_DecryptInit_ex(
            m_ctx, EVP_aes_128_cbc(), nullptr,
            reinterpret_cast<std::uint8_t*>(m_key.data()), reinterpret_cast<std::uint8_t*>(m_iv.data())
        );
    }


    bool AES_128_CBC::decryptUpdate(std::string_view cipherText, std::string& plainText)
    {
        assert(m_ctx);
        plainText.resize(cipherText.size());
        return EVP_DecryptUpdate(
            m_ctx,
            reinterpret_cast<std::uint8_t*>(plainText.data()), &m_textSizeAfterUpdate,
            reinterpret_cast<const std::uint8_t*>(cipherText.data()), static_cast<int>(cipherText.size())
        );
    }


    bool AES_128_CBC::decryptFinal(std::string &plainText)
    {
        assert(m_ctx);
        bool status = false;
        int lastPartLength = 0;

        status = EVP_DecryptFinal_ex(
            m_ctx,
            reinterpret_cast<std::uint8_t*>(plainText.data()) + m_textSizeAfterUpdate, &lastPartLength
        );
        if (status)
        {
            plainText.resize(m_textSizeAfterUpdate + lastPartLength);
        }

        return status;
    }

} // Crypto