add_library(plugs SHARED plugs.cpp)

target_include_directories(plugs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME} PRIVATE
        "G:/projects/repos/libraries/raylib/include"
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/include/engine
        ${CMAKE_SOURCE_DIR}/include/utils
        )

link_directories("G:/projects/repos/libraries/raylib/lib")

target_link_libraries(plugs PRIVATE
        "G:/projects/repos/libraries/raylib/lib/libraylib.a"
        winmm.dll gdi32.dll)
