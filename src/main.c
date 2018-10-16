#include "wolf3d.h"

int     ft_print_error(char *err)
{
    ft_putendl(err);
    return (EXIT_SUCCESS);
}

int     main(int argc, char **argv)
{
    t_env *env;
    int i;
    char *buf;

    i = -1;
    if (argc != 2)
        return (ft_print_error("Usage: ./wolf3d [map_file]"));
    if (!(env = init_env(get_map(argv[1]))))
        return (0);
    main_loop(env);
    remove_env(env);
    system("leaks wolf3d");
    return EXIT_SUCCESS;
}