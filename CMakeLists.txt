cmake_minimum_required(VERSION 3.10)
project(music_player C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

add_executable(music_player src/main.c)

# Include GTK4 headers
target_include_directories(music_player PRIVATE ${GTK4_INCLUDE_DIRS})

# Pass extra compile flags (from pkg-config)
target_compile_options(music_player PRIVATE ${GTK4_CFLAGS_OTHER})

# Link GTK4 libraries
target_link_libraries(music_player ${GTK4_LIBRARIES})
