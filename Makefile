NAME = wolf3d

SRC_WOLF = ./src/main.c ./src/floor_and_ceiling.c ./src/init_env.c ./src/raycast.c ./src/map.c ./src/remove_env.c ./src/sdl_helper.c ./src/textures.c ./src/keyboard_hooks.c ./src/colors_and_drawing.c

OBJECT_WOLF = $(SRC_WOLF:.c=.o)

FLAGS = -Wall -Wextra -O3

INCLUDES_WOLF = -I ./include/

INCLUDES_LIBFT = -I ./src/libft

INCLUDES_SDL2 = -I ./src/SDL/SDL2.framework/Headers

INCLUDES_SDL2_IMAGE = -I ./src/SDL/SDL2_image.framework/Headers

INCLUDES_SDL2_MIXER = -I ./src/SDL/SDL2_mixer.framework/Headers

LIBFT = ./src/libft/libft.a

INCLUDES_SDL2_TTF = -I ./src/SDL/SDL2_ttf.framework/Headers

FRAMEWORK_SDL2 = -F ./src/SDL -framework SDL2 \
	-framework SDL2_image \
	-framework SDL2_mixer

all: $(NAME)

$(NAME) : $(OBJECT_WOLF)
	make -C ./src/libft
	@echo "\033[0;32mWolf compiled\033[0;0m"
	@gcc -o $(NAME) $(FLAGS) $(LIBFT) $(INCLUDES_SDL2) $(INCLUDES_SDL2_IMAGE) -rpath @loader_path/src/sdl $(FRAMEWORK_SDL2) $(OBJECT_WOLF) $(INCLUDES_SDL2_MIXER) $(INCLUDES_SDL2_TTF)

%.o: %.c include/*.h
	gcc -g $(FLAGS) -o $@ -c $< $(INCLUDES_WOLF) $(INCLUDES_SDL2) $(INCLUDES_LIBFT) \
$(INCLUDES_SDL2_IMAGE) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

%.o: %.c
	gcc -g 	$(FLAGS) -o $@ -c $< $(INCLUDES_WOLF) $(INCLUDES_SDL2) $(INCLUDES_LIBFT) \
$(INCLUDES_SDL2_IMAGE) $(INCLUDES_SDL2_TTF) $(INCLUDES_SDL2_MIXER)

clean:
	make -C ./src/libft clean
	/bin/rm -f $(OBJECT_WOLF)

fclean: clean
	/bin/rm -f ./src/libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all
