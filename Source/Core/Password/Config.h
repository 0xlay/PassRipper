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
// File: Config.h
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Core::Password
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <string>


namespace Core::Password
{

    static constexpr char kNumericAlphabet[]    = "0123456789";
    static constexpr char kLowerCaseAlphabet[]  = "abcdefghijklmnopqrstuvwxyz";
    static constexpr char kUpperCaseAlphabet[]  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static_assert(sizeof(kNumericAlphabet)      == 10 + 1, "Invalid the kNumericalAlphabet");
    static_assert(sizeof(kLowerCaseAlphabet)    == 26 + 1, "Invalid the kLowerCaseAlphabet");
    static_assert(sizeof(kUpperCaseAlphabet)    == 26 + 1, "Invalid the kUpperCaseAlphabet");

    struct Range
    {
        std::size_t minLen = 1;
        std::size_t maxLen = 1;
    };

    struct Config
    {
        std::size_t numberOfPassword;
        std::string alphabet;
        Range       range;
    };

} // Core::Password