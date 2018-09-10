#include <stdbool.h>
#include "wolf3d.h"

void            key_down_events(t_env *env)
{
    double  rotSpeed = 0.1;
    double oldDirX = env->player->dir_x;
    double oldPlaneX = env->player->plane_x;
    double moveSpeed = 0.1;

    if (env->event.key.keysym.sym == SDLK_UP)
    {
        if(env->map->data[(int)(env->player->pos_x + env->player->dir_x * moveSpeed)][(int)(env->player->pos_y)] == '0') env->player->pos_x += env->player->dir_x * moveSpeed;
        if(env->map->data[(int)(env->player->pos_x)][(int)(env->player->pos_y + env->player->dir_y * moveSpeed)] == '0') env->player->pos_y += env->player->dir_y * moveSpeed;
        raycast(env);
    }
    //move backwards if no wall behind you
    if (env->event.key.keysym.sym == SDLK_DOWN)
    {
        if(env->map->data[(int)(env->player->pos_x - env->player->dir_x * moveSpeed)][(int)(env->player->pos_y)] == '0') env->player->pos_x -= env->player->dir_x * moveSpeed;
        if(env->map->data[(int)(env->player->pos_x)][(int)(env->player->pos_y - env->player->dir_y * moveSpeed)] == '0') env->player->pos_y -= env->player->dir_y * moveSpeed;
        raycast(env);
    }
    //rotate to the right
    if (env->event.key.keysym.sym == SDLK_RIGHT)
    {
        //both camera direction and camera plane must be rotated
        env->player->dir_x = env->player->dir_x * cos(-rotSpeed) - env->player->dir_y * sin(-rotSpeed);
        env->player->dir_y = oldDirX * sin(-rotSpeed) + env->player->dir_y * cos(-rotSpeed);
        env->player->plane_x = env->player->plane_x * cos(-rotSpeed) - env->player->plane_y * sin(-rotSpeed);
        env->player->plane_y = oldPlaneX * sin(-rotSpeed) + env->player->plane_y * cos(-rotSpeed);
        raycast(env);
    }
    if (env->event.key.keysym.sym == SDLK_LEFT)
    {
        env->player->dir_x = env->player->dir_x * cos(rotSpeed) - env->player->dir_y * sin(rotSpeed);
        env->player->dir_y = oldDirX * sin(rotSpeed) + env->player->dir_y * cos(rotSpeed);
        env->player->plane_x = env->player->plane_x * cos(rotSpeed) - env->player->plane_x * sin(rotSpeed);
        env->player->plane_y= oldPlaneX * sin(rotSpeed) + env->player->plane_y * cos(rotSpeed);
        raycast(env);
    }
}

void            key_up_events(t_env *env)
{

}

void            mouse_down_events(t_env *env)
{
//    if (env->event.button.button == SDL_BUTTON_LEFT)
//    {
//        double  rotSpeed = 4;
//        double oldDirX = env->player->dir_x;
//        env->player->dir_x = env->player->dir_x * cos(rotSpeed) - env->player->dir_y * sin(rotSpeed);
//        env->player->dir_y = oldDirX * sin(rotSpeed) + env->player->dir_y * cos(rotSpeed);
//        double oldPlaneX = env->player->plane_x;
//        env->player->plane_x = env->player->plane_x * cos(rotSpeed) - env->player->plane_x * sin(rotSpeed);
//        env->player->plane_y= oldPlaneX * sin(rotSpeed) + env->player->plane_y * cos(rotSpeed);
//    }
}

void            mouse_up_events(t_env *env)
{
//    if (env.event.button.button == SDL_BUTTON_LEFT)
//    {
//        SDL_SetRenderDrawColor(env.renderer, 12, 200, 110, 0);
//        SDL_RenderClear(env.renderer);
//        SDL_RenderPresent(env.renderer);
//    }
}

void            mouse_move_events(t_env *env)
{
//    if (env->event.motion.type == SDL_MOUSEMOTION)
//    {
//        SDL_SetRenderDrawColor(env->renderer, 0, 34, 0, 0);
//        SDL_RenderDrawPoint(env->renderer, env->event.button.x, env->event.button.y);
//        SDL_RenderDrawPoint(env->renderer, env->event.button.x + 1, env->event.button.y);
//        SDL_RenderDrawPoint(env->renderer, env->event.button.x - 1, env->event.button.y);
//        SDL_RenderDrawPoint(env->renderer, env->event.button.x, env->event.button.y - 1);
//        SDL_RenderDrawPoint(env->renderer, env->event.button.x, env->event.button.y + 1);
//        SDL_RenderPresent(env->renderer);
//    }
}
void            main_loop(t_env *env)
{
    bool    close_event;
    double moveSpeed = 3;

    close_event = false;
    raycast(env);
    while (!close_event)
    {
        while (SDL_PollEvent(&(env->event)))
        {
            if (env->event.type == SDL_QUIT)
                close_event = true;
            else if (env->event.type == SDL_KEYDOWN)
            {
                if (env->event.key.keysym.sym == SDLK_ESCAPE)
                    close_event = true;
                else
                    key_down_events(env);
            }
//            else if (env->event.type == SDL_KEYDOWN)
//                key_up_events(env);
//            else if (env->event.type == SDL_MOUSEBUTTONDOWN)
//                mouse_down_events(env);
//            else if (env->event.type == SDL_MOUSEBUTTONUP)
//                mouse_up_events(env);
//            if (env->event.type == SDL_MOUSEMOTION)
//                mouse_move_events(env);
        }
    }
}