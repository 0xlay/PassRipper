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
// File: SHA256.cpp
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Crypto
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <openssl/sha.h>
#include "SHA256.h"


namespace Crypto
{

    SHA256::SHA256()
        : m_ctx(std::make_unique<SHA256state_st>()), m_isInitialized(false)
    {
        if (m_ctx)
        {
            m_isInitialized = SHA256_Init(m_ctx.get());
        }
    }

    SHA256::~SHA256() noexcept
    { }

    SHA256::SHA256(SHA256 &&rhs) noexcept
        : SHA256()
    {
        std::swap(m_ctx, rhs.m_ctx);
        std::swap(m_isInitialized, rhs.m_isInitialized);
    }


    SHA256& SHA256::operator=(SHA256 &&rhs) noexcept
    {
        if (this != &rhs)
        {
            std::swap(m_ctx, rhs.m_ctx);
            std::swap(m_isInitialized, rhs.m_isInitialized);
        }
        return *this;
    }


    bool SHA256::update(std::string_view data)
    {
        bool status = false;

        if (m_isInitialized)
        {
            status = SHA256_Update(m_ctx.get(), data.data(), data.size());
        }

        return status;
    }


    std::vector<std::uint8_t> SHA256::complete()
    {
        std::vector<std::uint8_t> hash(SHA256_DIGEST_LENGTH);

        if (m_isInitialized)
        {
            SHA256_Final(hash.data(), m_ctx.get());
            m_isInitialized = SHA256_Init(m_ctx.get());
        }

        return hash;
    }

} // Crypto