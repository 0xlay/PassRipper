cmake_minimum_required(VERSION 3.20)
project(PassRipper VERSION 1.0.0.0 LANGUAGES CXX C)

set(INCLUDE

)

set(SOURCE
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE} ${INCLUDE})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra - pedantic -Werror)
endif()
