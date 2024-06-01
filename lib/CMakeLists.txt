set(SOURCES plugs.cpp ../src/engine/AnimationEngine.cpp ../src/engine/Particle.cpp)
add_library(plugs SHARED ${SOURCES})

target_include_directories(plugs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME} PRIVATE
        "G:/projects/repos/libraries/raylib/include"
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/utils
        ${CMAKE_SOURCE_DIR}/include/engine
        ${CMAKE_SOURCE_DIR}/include/OsSpecific
        ${CMAKE_SOURCE_DIR}/include/Interfaces
        )

link_directories("G:/projects/repos/libraries/raylib/lib")

target_link_libraries(plugs PUBLIC
        "G:/projects/repos/libraries/raylib/lib/libraylib.dll.a"
        winmm.dll gdi32.dll)