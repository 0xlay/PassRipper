cmake_minimum_required(VERSION 3.20)
project(PassRipperTest VERSION 1.0.0.0 LANGUAGES CXX C)

set(INCLUDE

)

set(SOURCE
    PasswordTest.cpp
    CryptoCipherTest.cpp
    CryptoHashTest.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE} ${INCLUDE})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "${PROJECT_ROOT_SOURCE_DIRECTORY}/Source/"
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE gtest gtest_main
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if(MSVC)
    add_compile_options(/W4 /WX)

    if (${CMAKE_SIZEOF_VOID_P} STREQUAL "8")
        message("Config for MSVC x64")

        #===============================================================================================================
        # Include OpenSSL for x64
        #===============================================================================================================

        target_include_directories(${PROJECT_NAME} PRIVATE ${OpenSSL}/x64/Release/include/)
        target_link_libraries(${PROJECT_NAME} PRIVATE libeay32)
        target_link_libraries(${PROJECT_NAME} PRIVATE ssleay32)

        #===============================================================================================================

    endif()
    if (${CMAKE_SIZEOF_VOID_P} STREQUAL "4")
        message("Config for MSVC x86")

        #===============================================================================================================
        # Include OpenSSL for x86
        #===============================================================================================================

        target_include_directories(${PROJECT_NAME} PRIVATE ${OpenSSL}/x86/Release/include/)
        target_link_libraries(${PROJECT_NAME} PRIVATE libeay32)
        target_link_libraries(${PROJECT_NAME} PRIVATE ssleay32)

        #===============================================================================================================

    endif()
else()
    add_compile_options(-Wall -Wextra - pedantic -Werror)
endif()
