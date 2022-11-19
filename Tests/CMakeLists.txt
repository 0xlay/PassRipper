cmake_minimum_required(VERSION 3.20)
project(PassRipperTest VERSION 1.0.0.0 LANGUAGES CXX C)

set(INCLUDE

)

set(SOURCE
    PasswordTest.cpp
    SampleTest.cpp
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

if (MSVC)
    target_compile_options(
        ${PROJECT_NAME} PRIVATE
        /W4 /WX
    )
else ()
    target_compile_options(
        ${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
