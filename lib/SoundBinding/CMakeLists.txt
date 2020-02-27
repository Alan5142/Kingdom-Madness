project(sound_sfml CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(sound_binding src/sound.cpp)

if (WIN32 AND NOT MSVC)
    set(ADDITIONAL_LINK_LIBS libstdc++)
else ()
    set(ADDITIONAL_LINK_LIBS "")
    set_target_properties(sound_binding PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif ()

target_link_libraries(sound_binding sfml-audio ${ADDITIONAL_LINK_LIBS})
target_include_directories(sound_binding PUBLIC include)