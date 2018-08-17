#include "wolf3d.h"

void	del_node(void *cont, size_t size)
{
    if (size)
        free(cont);
}