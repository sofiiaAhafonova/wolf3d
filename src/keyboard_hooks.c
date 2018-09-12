#include "wolf3d.h"


bool            rotate_right(t_env *env)
{
    double buf;

    if (env->event.key.keysym.sym != SDLK_RIGHT)
        return (false);
    buf = env->pl->dir.x;
    env->pl->dir.x = env->pl->dir.x * cos(-env->pl->rotation_speed)
            - env->pl->dir.y * sin(-env->pl->rotation_speed);
    env->pl->dir.y = buf * sin(-env->pl->rotation_speed)
            + env->pl->dir.y * cos(-env->pl->rotation_speed);
    buf = env->pl->plane.x;
    env->pl->plane.x = env->pl->plane.x * cos(-env->pl->rotation_speed)
            - env->pl->plane.y * sin(-env->pl->rotation_speed);
    env->pl->plane.y = buf * sin(-env->pl->rotation_speed)
            + env->pl->plane.y * cos(-env->pl->rotation_speed);
    return (true);
}

bool            rotate_left(t_env *env)
{
    double buf;

    if (env->event.key.keysym.sym != SDLK_LEFT)
        return (false);
    buf = env->pl->dir.x;
    env->pl->dir.x = env->pl->dir.x * cos(env->pl->rotation_speed)
            - env->pl->dir.y * sin(env->pl->rotation_speed);
    env->pl->dir.y =buf * sin(env->pl->rotation_speed)
            + env->pl->dir.y * cos(env->pl->rotation_speed);
    buf = env->pl->plane.x;
    env->pl->plane.x = env->pl->plane.x * cos(env->pl->rotation_speed)
            - env->pl->plane.y * sin(env->pl->rotation_speed);
    env->pl->plane.y= buf * sin(env->pl->rotation_speed)
            + env->pl->plane.y * cos(env->pl->rotation_speed);
    return (true);
}

bool            move_back_forth(t_env *env)
{
    if (env->event.key.keysym.sym == SDLK_UP)
    {
        if (env->map->data[(int)(env->pl->pos.x + env->pl->dir.x *
            env->pl->move_speed)][(int)(env->pl->pos.y)] == '0')
            env->pl->pos.x += env->pl->dir.x * env->pl->move_speed;
        if (env->map->data[(int)(env->pl->pos.x)][(int)(env->pl->pos.y +
            env->pl->dir.y * env->pl->move_speed)] == '0')
            env->pl->pos.y += env->pl->dir.y * env->pl->move_speed;
    }
    else if (env->event.key.keysym.sym == SDLK_DOWN)
    {
        if (env->map->data[(int)(env->pl->pos.x - env->pl->dir.x *
            env->pl->move_speed)][(int)(env->pl->pos.y)] == '0')
            env->pl->pos.x -= env->pl->dir.x * env->pl->move_speed;
        if (env->map->data[(int)(env->pl->pos.x)][(int)(env->pl->pos.y -
            env->pl->dir.y * env->pl->move_speed)] == '0')
            env->pl->pos.y -= env->pl->dir.y * env->pl->move_speed;
    }
    else
        return (false);
    return (true);
}

void            key_down_events(t_env *env)
{

    if (env->event.key.keysym.sym == SDLK_f)
    {
        if (!env->pl->accel)
        {
            env->pl->move_speed = 0.15;;
            env->pl->accel = true;
        }
        else
        {
            env->pl->move_speed = 0.05;;
            env->pl->accel = false;
        }
        return ;
    }
    else if (!move_back_forth(env) && !rotate_right(env) && !rotate_left(env))
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
//  }
}

void            mouse_up_events(t_env *env)
{
//    if (env.event.button.button == SDL_BUTTON_LEFT)
//    {
//    }
}

void            mouse_move_events(t_env *env)
{
//    if (env->event.motion.type == SDL_MOUSEMOTION)
//    {
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
//          else if (env->event.type == SDL_MOUSEBUTTONDOWN)
//              mouse_down_events(env);
//          else if (env->event.type == SDL_MOUSEBUTTONUP)
//              mouse_up_events(env);
//          if (env->event.type == SDL_MOUSEMOTION)
//                mouse_move_events(env);
        }
    }
}