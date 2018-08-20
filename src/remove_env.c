#include "wolf3d.h"

void	del_node(void *cont, size_t size)
{
    if (size && cont)
        free(cont);
}

void    remove_map(t_map *map)
{
    int i;

    if (!map)
        return ;
    i = -1;
    if (map->data)
    {
        while (++i < map->height)
            free(map->data[i]);
        free(map->data);
    }
    free(map);
}