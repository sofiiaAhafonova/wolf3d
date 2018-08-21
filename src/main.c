#include "wolf3d.h"
#include "libft.h"
#define WINDOW_WIDTH 600

int     ft_print_error(char *err)
{
    ft_putendl(err);
    return (EXIT_SUCCESS);
}

int     main(int argc, char **argv)
{
    t_env env;
    int i = -1;
    char *buf;
    if (argc != 2)
        return (ft_print_error("Usage: ./wolf3d [map_file]"));
    env.map = get_map(argv[1]);
    if (env.map)
    {
        while(++i < env.map->height)
        {
            buf = env.map->data[i];
            ft_putendl(buf);
        }
    }
    system("leaks wolf3d");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &(env.window), &(env.renderer));
    SDL_SetRenderDrawColor(env.renderer, 12, 200, 110, 0);
    SDL_RenderClear(env.renderer);
    SDL_RenderPresent(env.renderer);
    main_loop(env);
    remove_env(env);
    system("leaks wolf3d");
    return EXIT_SUCCESS;
}