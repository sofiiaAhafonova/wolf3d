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

    if (argc != 2)
        return (ft_print_error("Usage: ./wolf3d [map_file]"));

/*
t_env env;
int i;

ft_putendrt");
SDL_Init(SDL_INIT_VIDEO);
SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &(env.window), &(env.renderer));
SDL_SetRenderDrawColor(env.renderer, 0, 0, 0, 0);
SDL_RenderClear(env.renderer);
SDL_SetRenderDrawColor(env.renderer, 255, 0, 0, 255);
for (i = 0; i < WINDOW_WIDTH; ++i)
    SDL_RenderDrawPoint(env.renderer, i, i);
SDL_RenderPresent(env.renderer);
while (1)
{
    if (SDL_PollEvent(&env.event) && env.event.type == SDL_QUIT)
        break;
}
SDL_DestroyRenderer(env.renderer);
SDL_DestroyWindow(env.window);
SDL_Quit();
 */
    return EXIT_SUCCESS;
}