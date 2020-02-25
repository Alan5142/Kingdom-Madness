cmake_minimum_required(VERSION 3.15)
project(progra C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(lib/PDCurses)

add_executable(progra main.c
        src/start_screen.c
        src/game/game.c
        src/game/health.c)

target_link_libraries(progra PDcurses)
target_include_directories(progra PRIVATE include)