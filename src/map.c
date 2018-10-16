#include "wolf3d.h"

char		*cp_data(t_list *node, int width)
{
	int		i;
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * (width + 1))))
		return (0);
	i = -1;
	while (++i < width)
		str[i] = ((char*)node->content)[i];
	str[i] = 0;
	return (str);
}

int			check_line(char *line, int width)
{
	int i;

	i = 0;
	if (line[0] == '0')
		return (0);
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	if (line[i - 1] == '0')
		return (0);
	if (width == -1 || width == i)
		return (i);
	return (0);
}

int			check_result(t_map *map, bool has_zeroes)
{
	if (has_zeroes == false || map->height < 3 || map->width < 3)
	{
		ft_putendl("Wrong map data");
		remove_map(map);
		return (0);
	}
	return (1);
}

int			check_horizontal_line(t_map *map)
{
	int		i;
	int		j;
	bool	has_zeroes;

	i = -1;
	has_zeroes = false;
	while (++i < (int)map->height)
	{
		j = -1;
		while (++j < (int)map->width)
		{
			if (map->data[i][j] == '0')
				has_zeroes = true;
			if ((i == 0 || i == (int)map->height - 1) && map->data[i][j] == '0')
			{
				ft_putendl("Wrong map data");
				remove_map(map);
				return (0);
			}
		}
	}
	return (check_result(map, has_zeroes));
}

t_map		*create_map(t_list *lst, unsigned int w, unsigned int h)
{
	t_map	*map;
	t_list	*buf;

	if (!(map = (t_map *)malloc(sizeof(t_map))) || !lst ||
		!(map->data = (char**)malloc(sizeof(char*) * h)))
	{
		map ? free(map) : 0;
		lst ? ft_putendl("Map creating error") :
		ft_putendl("Wrong map file format");
		lst ? ft_lstdel(&lst, &del_node) : 0;
		return (NULL);
	}
	map->height = h;
	map->width = w;
	buf = lst;
	while (buf)
	{
		map->data[map->height - h] = cp_data(buf, w);
		buf = buf->next;
		h--;
	}
	ft_lstdel(&lst, &del_node);
	if (!check_horizontal_line(map))
		return (0);
	return (map);
}
