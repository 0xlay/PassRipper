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
// File: InputOutput.cpp
//
// Creator: 0xlay (0xlay.lab@gmail.com)
//
// Environment: User mode only
//
// Module: Utility::File
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "InputOutput.h"
#include <fstream>


namespace Utility::File
{

    bool WriteData(std::filesystem::path const& fullPath, std::string const& inputBuffer)
    {
        bool status = false;

        std::basic_ofstream<char> fileStream(fullPath, std::ios::binary);
        if (fileStream.is_open())
        {
            fileStream.write(&inputBuffer[0], inputBuffer.size());
            fileStream.close();
            status = true;
        }

        return status;
    }


    bool ReadData(std::filesystem::path const& fullPath, std::string& outputBuffer)
    {
        bool status = false;

        std::ifstream fileStream(fullPath, std::ios::binary | std::fstream::in);
        if (fileStream.is_open())
        {
            std::string buf(std::istreambuf_iterator<char>(fileStream), {});
            outputBuffer = std::move(buf);
            fileStream.close();
            status = true;
        }

        return status;
    }

} // Utility::File