#include <stdbool.h>
#include "wolf3d.h"

void            key_down_events(t_env env)
{

}

void            key_up_events(t_env env)
{

}

void            mouse_down_events(t_env env)
{
    if (env.event.button.button == SDL_BUTTON_LEFT)
    {
        SDL_SetRenderDrawColor(env.renderer, 0, 0, 0, 0);
        SDL_RenderClear(env.renderer);
        SDL_RenderPresent(env.renderer);
    }

}

void            mouse_up_events(t_env env)
{
    if (env.event.button.button == SDL_BUTTON_LEFT)
    {
        SDL_SetRenderDrawColor(env.renderer, 12, 200, 110, 0);
        SDL_RenderClear(env.renderer);
        SDL_RenderPresent(env.renderer);
    }
}

void            mouse_move_events(t_env env)
{
    if (env.event.motion.type == SDL_MOUSEMOTION)
    {
        SDL_SetRenderDrawColor(env.renderer, 0, 34, 0, 0);
        SDL_RenderDrawPoint(env.renderer, env.event.button.x, env.event.button.y);
        SDL_RenderDrawPoint(env.renderer, env.event.button.x + 1, env.event.button.y);
        SDL_RenderDrawPoint(env.renderer, env.event.button.x - 1, env.event.button.y);
        SDL_RenderDrawPoint(env.renderer, env.event.button.x, env.event.button.y - 1);
        SDL_RenderDrawPoint(env.renderer, env.event.button.x, env.event.button.y + 1);
        SDL_RenderPresent(env.renderer);
    }
}
void            main_loop(t_env env)
{
    bool    close_event;

    close_event = false;
    SDL_SetRenderDrawColor(env.renderer, 12, 200, 110, 0);
    SDL_RenderClear(env.renderer);
    SDL_RenderPresent(env.renderer);
    while (!close_event)
    {
        while (SDL_PollEvent(&env.event))
        {
            if (env.event.type == SDL_QUIT)
                close_event = true;
            else if (env.event.type == SDL_KEYDOWN)
            {
                if (env.event.key.keysym.sym == SDLK_ESCAPE)
                    close_event = true;
                else
                    key_down_events(env);
            }
            else if (env.event.type == SDL_KEYDOWN)
                key_up_events(env);
            else if (env.event.type == SDL_MOUSEBUTTONDOWN)
                mouse_down_events(env);
            else if (env.event.type == SDL_MOUSEBUTTONUP)
                mouse_up_events(env);
            if (env.event.type == SDL_MOUSEMOTION)
                mouse_move_events(env);
        }
    }
}