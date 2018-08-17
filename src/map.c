#include "wolf3d.h"
#include <fcntl.h>

int    check_line(char *line, int width)
{
    int i;

    i = 0;
    while(line[i])
    {
        if (!ft_isalnum(line[i]))
            return (0);
        i++;
    }
    if (width == -1)
        return (i);
    if (width != i)
        return (0);
    return (i);
}

t_map   *create_map(t_list *lst, int width)
{
    t_map   *map;

    if (!(map = (t_map *)malloc(sizeof(t_map))))
    {
        ft_putendl("Map creating error");
        return (NULL);
    }
    return (map);
}

t_map   *parse_map(int fd)
{
    t_list  *lst;
    char    *line;
    int     width;

    width = -1;
    while (get_next_line(fd, &line))
    {
        if (width == -1)
        {

        }
        if (!(width = check_line(line, width)))
        {
            ft_strdel(&line);
            lst ? ft_lstdel(&lst, &del_node) : 0;
            return (0);
        }
    }
    return (create_map(lst, width));
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