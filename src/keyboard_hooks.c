#include "wolf3d.h"


bool            rotation_keys(t_env *env)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = env->player->dir.x;
    old_plane_x = env->player->plane.x;
    if (env->event.key.keysym.sym == SDLK_RIGHT)
    {
        env->player->dir.x = env->player->dir.x * cos(-env->player->rotation_speed) - env->player->dir.y * sin(-env->player->rotation_speed);
        env->player->dir.y = old_dir_x * sin(-env->player->rotation_speed) + env->player->dir.y * cos(-env->player->rotation_speed);
        env->player->plane.x = env->player->plane.x * cos(-env->player->rotation_speed) - env->player->plane.y * sin(-env->player->rotation_speed);
        env->player->plane.y = old_plane_x * sin(-env->player->rotation_speed) + env->player->plane.y * cos(-env->player->rotation_speed);
    }
    else if (env->event.key.keysym.sym == SDLK_LEFT)
    {
        env->player->dir.x = env->player->dir.x * cos(env->player->rotation_speed) - env->player->dir.y * sin(env->player->rotation_speed);
        env->player->dir.y = old_dir_x * sin(env->player->rotation_speed) + env->player->dir.y * cos(env->player->rotation_speed);
        env->player->plane.x = env->player->plane.x * cos(env->player->rotation_speed) - env->player->plane.y * sin(env->player->rotation_speed);
        env->player->plane.y= old_plane_x * sin(env->player->rotation_speed) + env->player->plane.y * cos(env->player->rotation_speed);
    }
    else
        return (false);
    return (true);
}

void            key_down_events(t_env *env)
{

    if (env->event.key.keysym.sym == SDLK_f)
    {
        if (!env->player->accel)
        {
            env->player->move_speed = 0.15;;
            env->player->accel = true;
        }
        else
        {
            env->player->move_speed = 0.05;;
            env->player->accel = false;
        }
        return ;
    }
    if (env->event.key.keysym.sym == SDLK_UP)
    {
        if(env->map->data[(int)(env->player->pos.x + env->player->dir.x * env->player->move_speed)][(int)(env->player->pos.y)] == '0') env->player->pos.x += env->player->dir.x * env->player->move_speed;
        if(env->map->data[(int)(env->player->pos.x)][(int)(env->player->pos.y + env->player->dir.y * env->player->move_speed)] == '0') env->player->pos.y += env->player->dir.y * env->player->move_speed;
    }
    else if (env->event.key.keysym.sym == SDLK_DOWN)
    {
        if(env->map->data[(int)(env->player->pos.x - env->player->dir.x * env->player->move_speed)][(int)(env->player->pos.y)] == '0') env->player->pos.x -= env->player->dir.x * env->player->move_speed;
        if(env->map->data[(int)(env->player->pos.x)][(int)(env->player->pos.y - env->player->dir.y * env->player->move_speed)] == '0') env->player->pos.y -= env->player->dir.y * env->player->move_speed;
    } else if (!rotation_keys(env))
        return;
    raycast(env);
}

void            key_up_events(t_env *env)
{
}

void            mouse_down_events(t_env *env)
{
//    if (env->event.button.button == SDL_BUTTON_LEFT)
//    {
//        double  env->player->rotation_speed = 4;
//        double oldDirX = env->player->dir_x;
//        env->player->dir_x = env->player->dir_x * cos(env->player->rotation_speed) - env->player->dir_y * sin(env->player->rotation_speed);
//        env->player->dir_y = oldDirX * sin(env->player->rotation_speed) + env->player->dir_y * cos(env->player->rotation_speed);
//        double oldPlaneX = env->player->plane_x;
//        env->player->plane_x = env->player->plane_x * cos(env->player->rotation_speed) - env->player->plane_x * sin(env->player->rotation_speed);
//        env->player->plane_y= oldPlaneX * sin(env->player->rotation_speed) + env->player->plane_y * cos(env->player->rotation_speed);
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
            else if (env->event.type == SDL_KEYUP)
                key_up_events(env);
//            else if (env->event.type == SDL_MOUSEBUTTONDOWN)
//                mouse_down_events(env);
//            else if (env->event.type == SDL_MOUSEBUTTONUP)
//                mouse_up_events(env);
//            if (env->event.type == SDL_MOUSEMOTION)
//                mouse_move_events(env);
        }
    }
}