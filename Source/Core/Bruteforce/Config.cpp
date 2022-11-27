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
// File: Config.cpp
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Core::Bruteforce
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Config.h"


namespace Core::Bruteforce
{

    Config ParseToConfig(nlohmann::json const& json)
    {
        Config config{};
        nlohmann::json::const_iterator  it{};

        if (it = json.find("alphabet"); it != json.end())
        {
            config.alphabet = it.value();
        }
        if (it = json.find("passwordLength"); it != json.end())
        {
            config.passwordLength = it.value();
        }
        if (it = json.find("threadCount"); it != json.end())
        {
            config.threadCount = it.value();
        }
        if (it = json.find("pathToLogFile"); it != json.end())
        {
            config.pathToLogFile = it.value();
        }

        return config;
    }

} // Core::Bruteforce