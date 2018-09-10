cmake_minimum_required(VERSION 3.9)
project(wolf3d C)

set(CMAKE_C_STANDARD 99)
find_package(SDL2 REQUIRED)
link_directories(libft)
include_directories(${SDL2_INCLUDE_DIRS} include libft)

set ( PROJECT_LINK_LIBS libft.a)
set (LINKED_LIBS -lm)
add_executable(wolf3d src/main.c include/wolf3d.h src/map.c src/remove_env.c src/keyboard_hooks.c src/init_env.c src/raycast.c src/example.cpp)
target_link_libraries(wolf3d ${SDL2_LIBRARIES} ${PROJECT_LINK_LIBS} -Werror -Wextra -Wall -O3 ${LINKED_LIBS} )

