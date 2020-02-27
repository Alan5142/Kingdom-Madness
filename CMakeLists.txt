cmake_minimum_required(VERSION 3.15)
project(progra C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(lib/PDCurses)
add_subdirectory(lib/SFML)
add_subdirectory(lib/SoundBinding)

add_definitions(-DPDC_WIDE=1)
add_executable(progra main.c
        src/start_screen.c
        src/game/game.c
        src/game/health.c
        src/play_music.c
        src/game/score.c
        src/utils/colors.c)

target_link_libraries(progra PDcurses winmm sound_binding)
target_include_directories(progra PRIVATE include)

add_custom_command(TARGET progra POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/SFML/extlibs/bin/x64/openal32.dll ${CMAKE_BINARY_DIR})