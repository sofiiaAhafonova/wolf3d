cmake_minimum_required(VERSION 3.9)
project(wolf3d C)

set(CMAKE_C_STANDARD 99)
find_package(SDL2 REQUIRED)
link_directories(src/libft)
include_directories(${SDL2_INCLUDE_DIRS} include src/libft)

set ( PROJECT_LINK_LIBS libft.a)
set (LINKED_LIBS -lm -lSDL2_mixer -lSDL2_image -lSDL2_ttf)
add_executable(wolf3d  src/main.c include/wolf3d.h src/map.c src/remove_env.c src/keyboard_hooks.c src/init_env.c src/raycast.c
        src/sdl_helper.c src/textures.c src/floor_and_ceiling.c src/colors_and_drawing.c)
target_link_libraries(wolf3d ${SDL2_LIBRARIES} ${PROJECT_LINK_LIBS} -Werror -Wextra -Wall -O3 ${LINKED_LIBS} )

