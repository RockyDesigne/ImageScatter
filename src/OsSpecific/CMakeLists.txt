project(ImageScatter)

set(SOURCES
        Plugin.cpp
        WindowsObject.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Interfaces
        ${CMAKE_SOURCE_DIR}/include/OsSpecific
        )

link_directories("G:/projects/repos/libraries/raylib/lib")

target_link_libraries(${PROJECT_NAME} PRIVATE
        winmm.dll gdi32.dll user32.dll shell32.dll kernel32.dll)
