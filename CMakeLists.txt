cmake_minimum_required(VERSION 3.10)
project(music_player C)

set(CMAKE_C_STANDARD 23)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MPG123 REQUIRED IMPORTED_TARGET libmpg123)

# List all source files
file(GLOB SOURCES "src/*.c")
add_executable(music_player ${SOURCES})

# for including libmpg123 headers
target_include_directories(music_player PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${MPG123_INCLUDE_DIRS}
)

target_compile_options(music_player PRIVATE
    ${MPG123_CFLAGS_OTHER}
)

target_link_libraries(music_player PRIVATE
    PkgConfig::MPG123
)
