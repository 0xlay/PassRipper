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
// File: Generate.cpp
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Core::Password
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "Generate.h"


namespace Core::Password
{

    std::string GetInitializedSpinners(Range const& passwordRange)
    {
        std::string spinners(passwordRange.maxLen, '\0');

        for (std::size_t i = 0; i <= passwordRange.minLen; ++i)
        {
            spinners[i] = 'a';
        }

        return spinners;
    }


    std::vector<int> GetInitializedCountersForSpinners(Range const& passwordRange)
    {
        std::vector<int> spinCounters(passwordRange.maxLen, -1);

        for (std::size_t i = 0; i <= passwordRange.minLen; ++i)
        {
            spinCounters[i] = 0;
        }

        return spinCounters;
    }


    bool NextSpin(std::string_view alphabet, std::string& spinners, std::vector<int>& spinCounters)
    {
        std::size_t i = 0;

        while (spinCounters[i] == static_cast<int>(alphabet.size()))
        {
            if (i == spinners.size() - 1)
            {
                return false;
            }

            spinCounters[i] = 0;
            spinCounters[++i] += 1;
        }

        for (std::size_t j = 0; j <= i; ++j)
        {
            if (j < spinners.size())
                spinners[j] = alphabet[spinCounters[j]];
        }

        ++spinCounters[0];

        return true;
    }


    std::vector<std::string> Generate(Config const& config)
    {
        std::vector<std::string> passwords(config.numberOfPassword);
        std::string spinners = GetInitializedSpinners(config.range);
        std::vector<int> spinCounters = GetInitializedCountersForSpinners(config.range);

        for (std::size_t it = 0; it < config.numberOfPassword; ++it)
        {
            if (!NextSpin(config.alphabet, spinners, spinCounters))
                break;
            passwords[it] = spinners.c_str();
        }

        return passwords;
    }

} // Core::Password