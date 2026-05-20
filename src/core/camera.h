#ifndef CAMERA_H
#define CAMERA_H



typedef struct{
    float x; // world space position X the camera is looking at
    float y; // world space position Y the camera is looking at
    float offset_x;
    float offset_y;
    float zoom; // 1 default 2 zoomed in and 0.5 zommed out
}Camera2D;

// transforms
void camera_world_to_screen(
        const Camera2D *self,
        float world_x,
        float world_y,
        float screen_w,
        float screen_h,
        float *out_screen_x,
        float *out_screen_y);

void camera_screen_to_world(
        const Camera2D *self,
        float screen_x,
        float screen_y,
        float screen_w,
        float screen_h,
        float *out_world_x,
        float *out_world_y);

void camera_update_smooth_follow(Camera2D *self,float target_x, float target_y, float smoothness);


float camera_world_to_screen_size(Camera2D *camera, float size);

// void camera_update(EngineState *engine_state);

SDL_FPoint camera_screen_to_world_r(
    const Camera2D *self,
    float screen_x,
    float screen_y
    );

SDL_FPoint camera_screen_to_world_r2(
    const Camera2D *self,
    float screen_x,
    float screen_y,
    float world_x,
    float world_y
    );

SDL_FPoint camera_world_to_screen_r(
        const Camera2D *self,
        float world_x,
        float world_y
        );

void camera_teleport(
        Camera2D *self,
        float world_x,
        float world_y);

#endif // CAMERA_H
