cmake_minimum_required(VERSION 3.15)
project(progra C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(lib/PDCurses)
add_subdirectory(lib/SFML)
add_subdirectory(lib/SoundBinding)

add_definitions(-DPDC_WIDE=1)
add_executable(progra WIN32 main.c
        src/start_screen.c
        src/game/game.c
        src/game/health.c
        src/game/inventory.c
        src/game/score.c
        src/utils/colors.c
        src/utils/menu.c
        src/game/pause.c
        src/utils/sprite.c
        src/utils/render_graph.c
        src/game/store.c
        src/game/game_data.c
        src/player/player.c src/load_game.c)

target_link_libraries(progra PDcurses winmm sound_binding shlwapi)
target_include_directories(progra PRIVATE include)

if (MSVC)
    target_compile_options(progra PRIVATE /W4 /WX /wd4005 /wd4244 -D_CRT_SECURE_NO_WARNINGS)
else ()
    target_compile_options(progra PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()

add_custom_target(copy_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/SFML/extlibs/bin/x64/openal32.dll ${CMAKE_BINARY_DIR})

add_dependencies(progra copy_resources)
