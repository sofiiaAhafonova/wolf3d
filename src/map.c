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
    while(line[i])
    {
        if (!ft_isdigit(line[i]))
            return (0);
        i++;
    }
    if (width == -1 || width == i)
        return (i);
    return (0);
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