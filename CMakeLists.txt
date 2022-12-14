cmake_minimum_required(VERSION 3.20)
project(PassRipper VERSION 1.0.0.0 LANGUAGES CXX C)

set(PROJECT_ROOT_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(OpenSSL ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/OpenSSL/build)

set(INCLUDE
    Source/Argument.h
    Source/Core/Bruteforce.h
    Source/Core/Bruteforce/Config.h
    Source/Core/Bruteforce/Engine.h
    Source/Core/Password.h
    Source/Core/Password/Config.h
    Source/Core/Password/Generate.h
    Source/Crypto/Cipher.h
    Source/Crypto/Cipher/ICipher.h
    Source/Crypto/Cipher/AES_128_CBC.h
    Source/Crypto/Hash.h
    Source/Crypto/Hash/IHash.h
    Source/Crypto/Hash/SHA256.h
    Source/Utility/String.h
    Source/Utility/String/Compare.h
    Source/Utility/String/Convert.h
    Source/Utility/File.h
    Source/Utility/File/InputOutput.h
    Source/Crypto/Hash/Utility.h
)

set(SOURCE
    Source/Argument.cpp
    Source/Main.cpp
    Source/Core/Bruteforce/Config.cpp
    Source/Core/Bruteforce/Engine.cpp
    Source/Core/Password/Generate.cpp
    Source/Crypto/Cipher.cpp
    Source/Crypto/Cipher/AES_128_CBC.cpp
    Source/Crypto/Hash.cpp
    Source/Crypto/Hash/SHA256.cpp
    Source/Utility/String/Compare.cpp
    Source/Utility/String/Convert.cpp
    Source/Utility/File/InputOutput.cpp
    Source/Crypto/Hash/Utility.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE} ${INCLUDE})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_ROOT_SOURCE_DIRECTORY}/Source)

if(MSVC)
    add_compile_options(/W4 /WX)

    if (${CMAKE_SIZEOF_VOID_P} STREQUAL "8")
        message("Config for MSVC x64")

        #===============================================================================================================
        # Include OpenSSL for x64
        #===============================================================================================================

        target_include_directories(${PROJECT_NAME} PRIVATE ${OpenSSL}/x64/Release/include/)

        add_library(libeay32 STATIC IMPORTED GLOBAL)
        set_target_properties(libeay32 PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL}/x64/Release/include/"
            IMPORTED_LOCATION "${OpenSSL}/x64/Release/lib/libeay32.lib"
        )
        target_link_libraries(${PROJECT_NAME} PRIVATE libeay32)

        add_library(ssleay32 STATIC IMPORTED GLOBAL)
        set_target_properties(ssleay32 PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL}/x64/Release/include/"
            IMPORTED_LOCATION "${OpenSSL}/x64/Release/lib/ssleay32.lib"
        )
        target_link_libraries(${PROJECT_NAME} PRIVATE ssleay32)

        #===============================================================================================================

    endif()
    if (${CMAKE_SIZEOF_VOID_P} STREQUAL "4")
        message("Config for MSVC x86")

        #===============================================================================================================
        # Include OpenSSL for x86
        #===============================================================================================================

        target_include_directories(${PROJECT_NAME} PRIVATE ${OpenSSL}/x86/Release/include/)

        add_library(libeay32 STATIC IMPORTED GLOBAL)
        set_target_properties(libeay32 PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL}/x86/Release/include/"
            IMPORTED_LOCATION "${OpenSSL}/x86/Release/lib/libeay32.lib"
        )
        target_link_libraries(${PROJECT_NAME} PRIVATE libeay32)

        add_library(ssleay32 STATIC IMPORTED GLOBAL)
        set_target_properties(ssleay32 PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${OpenSSL}/x86/Release/include/"
            IMPORTED_LOCATION "${OpenSSL}/x86/Release/lib/ssleay32.lib"
        )
        target_link_libraries(${PROJECT_NAME} PRIVATE ssleay32)

        #===============================================================================================================

    endif()
else()
    add_compile_options(-Wall -Wextra - pedantic -Werror)
endif()

#=======================================================================================================================
# Nlohmann json
#=======================================================================================================================

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Json)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)


#=======================================================================================================================
# Google test
#=======================================================================================================================

enable_testing()

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GoogleTest/"
)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/Tests/"
)
