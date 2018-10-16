#include "wolf3d.h"
#include <fcntl.h>

char *cp_data(t_list *node, int width)
{
    int     i;
    char    *str;

    if (!(str = (char*)malloc(sizeof(char) * (width + 1))))
        return (0);
    i = -1;
    while (++i < width)
        str[i] = ((char*)node->content)[i];
    str[i] = 0;
    return (str);
}

int    check_line(char *line, int width)
{
    int i;

    i = 0;
    if (line[0] == '0')
        return (0);
    while(line[i])
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

int check_horizontal_line(t_map *map)
{
    int     i;
    int     j;
    bool    has_zeroes;

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
    if (has_zeroes == false || map->height < 3 || map->width < 3)
    {
        ft_putendl("Wrong map data");
        remove_map(map);
        return (0);
    }
    return (1);
}

t_map   *create_map(t_list *lst, unsigned int width, unsigned int height)
{
    t_map   *map;
    t_list  *buf;

    map = NULL;
    if (!lst || !(map = (t_map *)malloc(sizeof(t_map))) ||
        !(map->data = (char**)malloc(sizeof(char*) * height)))
    {
        map ? free(map) : 0;
        lst ? ft_putendl("Map creating error") :
        ft_putendl("Wrong map file format");
        lst ? ft_lstdel(&lst, &del_node) : 0;
        return (NULL);
    }
    map->height = height;
    map->width = width;
    buf = lst;
    while (buf)
    {
        map->data[map->height - height] = cp_data(buf, width);
        buf = buf->next;
        height--;
    }
    ft_lstdel(&lst, &del_node);
    if (!check_horizontal_line(map))
        return (0);
    return (map);
}

t_map   *parse_map(int fd)
{
    t_list          *lst;
    t_list	        *node;
    char            *line;
    int             width;
    unsigned int    height;

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

t_map   *get_map(char *file_name)
{

    int     fd;

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