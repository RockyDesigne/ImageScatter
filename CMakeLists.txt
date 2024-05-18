cmake_minimum_required(VERSION 3.25)
project(imageBanana)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES ./src/main.cpp)

add_executable(imageBanana ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wshadow)

target_include_directories(${PROJECT_NAME} PRIVATE "G:/projects/repos/libraries/raylib/include")

link_directories("G:/projects/repos/libraries/raylib/lib")

target_link_libraries(${PROJECT_NAME} PRIVATE
        "G:/projects/repos/libraries/raylib/lib/libraylib.a"
        winmm.lib gdi32.lib user32.lib shell32.lib)