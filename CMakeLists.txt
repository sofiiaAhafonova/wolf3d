cmake_minimum_required(VERSION 3.9)
project(wolf3d C)

set(CMAKE_C_STANDARD 99)
find_package(SDL2 REQUIRED)
link_directories(src/libft)
include_directories(${SDL2_INCLUDE_DIRS} include src/libft)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/libft/libft.a COMMAND make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/libft)

add_custom_target(extern_lib DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/libft/libft.a)


set (LINKED_LIBS -lm -lSDL2_mixer -lSDL2_image)
add_executable(wolf3d  src/main.c include/wolf3d.h src/map.c src/remove_env.c src/keyboard_hooks.c src/init_env.c src/raycast.c
        src/sdl_helper.c src/textures.c src/floor_and_ceiling.c src/colors_and_drawing.c)
target_link_libraries(wolf3d ${SDL2_LIBRARIES} ${LINKED_LIBS} ${CMAKE_CURRENT_SOURCE_DIR}/src/libft/libft.a -Werror -Wextra -Wall -O3 )
add_dependencies(wolf3d extern_lib)
