project(sound_sfml CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(sound_binding src/sound.cpp)
target_link_libraries(sound_binding sfml-audio libstdc++)
target_include_directories(sound_binding PUBLIC include)