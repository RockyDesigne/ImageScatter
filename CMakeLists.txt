cmake_minimum_required(VERSION 3.25)
project(imageBanana)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

set(SOURCES src/main.cpp
        src/OsSpecific/Plugin.cpp
        src/OsSpecific/WindowsObject.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wshadow)

# Add include directories specifically for the target
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/utils
        ${CMAKE_SOURCE_DIR}/include/OsSpecific
        ${CMAKE_SOURCE_DIR}/include/Interfaces
        "G:/projects/repos/libraries/raylib/include"
        )

link_directories("G:/projects/repos/libraries/raylib/lib")

target_link_libraries(${PROJECT_NAME} PRIVATE
        "G:/projects/repos/libraries/raylib/lib/libraylib.dll.a"
        winmm.dll gdi32.dll
        )