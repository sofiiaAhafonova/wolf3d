NAME = wolf3d

# Project builds and dirs
SRCDIR = ./src/
SRCNAMES = main.c
SRC = $(addprefix $(SRCDIR), $(SRCNAMES))
INC = ./include/
BUILDDIR = ./build/
BUILDOBJS = $(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))

# Libft builds and dirs
# LIBDIR = ./libft/
# LIBFT = ./libft/libft.a
# LIBINC = ./libft/

# Optimization and Compiler flags and commands
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Debugging flags
DEBUG =

# Main rule
all: $(BUILDDIR) $(LIBFT) $(NAME)

# Object dir rule
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Objects rule
$(BUILDDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) -I$(LIBINC) -I$(INC) -o $@ -c $<

# Project file rule
$(NAME): $(BUILDOBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(BUILDOBJS) -L/Users/sahafono/.brew/Cellar/sdl2/2.0.8/lib -lSDL2
# $(LIBFT) -lm -lmlx -framework OpenGL -framework AppKit

# Libft rule
$(LIBFT):
	make -C $(LIBDIR)

# Cleaning up the build files
clean:
	rm -rf $(BUILDDIR)
	make -C $(LIBDIR) clean

# Getting rid of the project file
fclean: clean
	rm -rf $(NAME)
	make -C $(LIBDIR) fclean

# Do both of the above
re: fclean all

# Just in case those files exist in the root dir
.PHONY: all fclean clean re
.NOTPARALLEL:  all clean fclean re