cmake_minimum_required(VERSION 3.25)
project(imageBanana)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

set(SOURCES ./src/main.cpp src/Particle.cpp src/Plugin.cpp)

include_directories(include)

set(HEADERS ./include/Constants.h ./include/Particle.h include/Plugin.h)

add_executable(imageBanana ${SOURCES} ${HEADERS})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wshadow)

target_include_directories(${PROJECT_NAME} PRIVATE "G:/projects/repos/libraries/raylib/include" ${CMAKE_SOURCE_DIR}/lib)

link_directories("G:/projects/repos/libraries/raylib/lib")

target_link_libraries(${PROJECT_NAME} PRIVATE
        "G:/projects/repos/libraries/raylib/lib/libraylib.a"
        winmm.lib gdi32.lib user32.lib shell32.lib kernel32.lib plugs)