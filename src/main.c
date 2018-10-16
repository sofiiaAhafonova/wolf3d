#include "wolf3d.h"
#include <fcntl.h>

int					ft_print_error(char *err)
{
	ft_putendl(err);
	return (EXIT_SUCCESS);
}

t_map				*parse_map(int fd)
{
	t_list			*lst;
	t_list			*node;
	char			*line;
	int				width;
	unsigned int	height;

	width = -1;
	lst = NULL;
	height = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (!(width = check_line(line, width)))
		{
			line ? ft_strdel(&line) : 0;
			lst ? ft_lstdel(&lst, &del_node) : 0;
			ft_putendl("Wrong map data");
			return (NULL);
		}
		node = ft_lstnew(line, sizeof(char) * ft_strlen(line));
		ft_lstadd(&lst, node);
		ft_strdel(&line);
		height++;
	}
	return (create_map(lst, (unsigned int)width, height));
}

t_map				*get_map(char *file_name)
{
	int fd;

	if (!file_name)
		return (NULL);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl("Wrong map format");
		return (NULL);
	}
	return (parse_map(fd));
}

int					main(int argc, char **argv)
{
	t_env			*env;
	int				i;

	i = -1;
	if (argc != 2)
		return (ft_print_error("Usage: ./wolf3d [map_file]"));
	if (!(env = init_env(get_map(argv[1]))))
		return (0);
	main_loop(env);
	remove_env(env);
	system("leaks wolf3d");
	return (EXIT_SUCCESS);
}
