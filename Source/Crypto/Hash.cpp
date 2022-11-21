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
// File: Hash.cpp
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Crypto
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iomanip>
#include <sstream>
#include "Hash.h"
#include "Hash/IHash.h"


namespace Crypto
{

    Hash::Hash(std::unique_ptr<IHash> hash)
        : m_hash(std::move(hash))
    {}


    bool Hash::generate(std::string_view data)
    {
        return m_hash->update(data);
    }


    std::vector<std::uint8_t> Hash::toBytes()
    {
        return m_hash->complete();
    }


    std::string Hash::toHexString()
    {
        std::stringstream hashStream;
        std::vector<std::uint8_t> hashInBytes = m_hash->complete();

        if (!hashInBytes.empty())
        {
            hashStream << std::hex << std::setfill('0');
            for (auto && symbol : hashInBytes)
            {
                hashStream << std::setw(2) << static_cast<unsigned>(symbol);
            }
        }

        return hashStream.str();
    }

} // Crypto