#include "camera.h"

#include "engine_state.h"

SDL_FPoint camera_world_to_screen_r(
        const Camera2D *self,
        float world_x,
        float world_y
        )
{
    SDL_FPoint res;

    res.x = (world_x - self->x) * self->zoom + self->offset_x;
    res.y = (world_y - self->y) * self->zoom + self->offset_y;

    return res;
}


void camera_world_to_screen(
        const Camera2D *self,
        float world_x,
        float world_y,
        float screen_w,
        float screen_h,
        float *out_screen_x,
        float *out_screen_y){

    // center camera, subtract camera position from world position
    float relative_x = world_x - self->x;
    float relative_y = world_y - self->y;

    // apply zoom
    relative_x *= self->zoom;
    relative_y *= self->zoom;

    // offset to screen center
    *out_screen_x = relative_x + (screen_w * 0.5f);
    *out_screen_y = relative_y + (screen_h * 0.5f);
}

SDL_FPoint camera_screen_to_world_r(
    const Camera2D *self,
    float screen_x,
    float screen_y
    )
{
    // // reverse the screen center offset
    // float relative_x = screen_x - self->offset_x;
    // float relative_y = screen_y - self->offset_y;

    // // reverse zoom
    // relative_x /= self->zoom;
    // relative_y /= self->zoom;

    // SDL_FPoint res;
    // // add camera position
    // res.x = relative_x - self->x;
    // res.y = relative_y - self->y;
    return (SDL_FPoint){
            .x = (screen_x - self->offset_x) / self->zoom + self->x,
            .y = (screen_y - self->offset_y) / self->zoom + self->y,
        };

    // return res;
}

void camera_screen_to_world(
        const Camera2D *self,
        float screen_x,
        float screen_y,
        float screen_w,
        float screen_h,
        float *out_world_x,
        float *out_world_y){

    // reverse the screen center offset
    float relative_x = screen_x - (screen_w * 0.5f);
    float relative_y = screen_y - (screen_h * 0.5f);

    // reverse zoom
    relative_x /= self->zoom;
    relative_y /= self->zoom;

    // add camera position
    *out_world_x = relative_x - self->x;
    *out_world_y = relative_y - self->y;
}

void camera_update_smooth_follow(Camera2D *self, float target_x, float target_y,  float smoothness)
{

    // float camera_x = -(engine_state->window_width * 0.5f);
    // float camera_y = -(engine_state->window_height * 0.5f);


    // recommendation is 0.1 for even fell
    // camera->x += ((target_x * es->window_width) - camera->x) * smoothness;
    // camera->y += ((target_y * es->window_height) - camera->y) * smoothness;

    self->x += (target_x - self->x) * smoothness;
    self->y += (target_y - self->y) * smoothness;

    // self->x = 2.5;
    // self->y = 2.5;
}
float camera_world_to_screen_size(Camera2D *camera, float size){
    return size * camera->zoom;
}
