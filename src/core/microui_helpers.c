#include "microui_helpers.h"

int text_width(mu_Font font, const char *text, int len) {
    int res = 0;
    for (const char *p = text; *p && len--; p++) {
        if ((*p & 0xc0) == 0x80) { continue; }
        int chr = mu_min((unsigned char) *p, 127);
        res += atlas[ATLAS_FONT + chr].w;
    }
    return res;
}

int text_height(mu_Font font) {
    return 18;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void window_microui(mu_Context *ctx, SDL_Renderer *renderer, AssetManager *asset_manager)
{
    mu_begin(ctx);
    if(mu_begin_window(ctx,"test",mu_rect(10,10,300,400))){
        // process ui
        if (mu_button(ctx, "My Button")) {
            SDL_Log("TEST!");
        }
        mu_end_window(ctx);
    }

    mu_end(ctx);

    SDL_Texture *tex = asset_manager->microui.texture;

    // SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    // SDL_RenderClear(renderer);

    // UI drawing
    mu_Command *cmd = NULL;

    while(mu_next_command(ctx, &cmd)) {
        if(cmd->type == MU_COMMAND_TEXT) {
            SDL_FRect dest;
            dest.x = cmd->text.pos.x;
            dest.y = cmd->text.pos.y;

            for(const char *p = cmd->text.str; *p; p++) {
                if((*p & 0xc0) == 0x80) { continue; }
                int chr = min((unsigned char) *p, 127);
                mu_Rect src = atlas[ATLAS_FONT + chr];
                dest.w = src.w;
                dest.h = src.h;

                SDL_FRect srcSDL;
                srcSDL.h = src.h;
                srcSDL.w = src.w;
                srcSDL.x = src.x;
                srcSDL.y = src.y;

                // // before rendering text commands
                // SDL_SetTextureColorMod(tex, cmd->text.color.r, cmd->text.color.g, cmd->text.color.b);

                SDL_RenderTexture(renderer, tex, &srcSDL, &dest);
                dest.x += dest.w;
            }
        }
        if(cmd->type == MU_COMMAND_RECT) {
            SDL_FRect rect;
            rect.h = cmd->rect.rect.h;
            rect.w = cmd->rect.rect.w;
            rect.x = cmd->rect.rect.x;
            rect.y = cmd->rect.rect.y;

            SDL_SetRenderDrawColor(renderer, cmd->rect.color.r, cmd->rect.color.g, cmd->rect.color.b, cmd->rect.color.a);
            SDL_RenderFillRect(renderer, &rect);

        }
        if(cmd->type == MU_COMMAND_ICON) {
            SDL_FRect rect;
            rect.h = cmd->icon.rect.h;
            rect.w = cmd->icon.rect.w;
            rect.x = cmd->icon.rect.x;
            rect.y = cmd->icon.rect.y;

            mu_Rect r = atlas[cmd->icon.id];
            SDL_FRect srect;
            srect.h = r.h;
            srect.w = r.w;
            srect.x = r.x;
            srect.y = r.y;

            SDL_RenderTexture(renderer, tex, &srect, &rect);

        }
        if(cmd->type == MU_COMMAND_CLIP) {
            if (cmd->clip.rect.w > 0) {
                // convert logical → physical for clip rect
                float x = cmd->clip.rect.x;
                float y = cmd->clip.rect.y;
                float w = cmd->clip.rect.w;
                float h = cmd->clip.rect.h;

                float px1, py1, px2, py2;
                SDL_RenderCoordinatesToWindow(renderer, x,     y,     &px1, &py1);
                SDL_RenderCoordinatesToWindow(renderer, x + w, y + h, &px2, &py2);

                SDL_Rect clip = {
                    (int)px1, (int)py1,
                    (int)(px2 - px1), (int)(py2 - py1)
                };
                SDL_SetRenderClipRect(renderer, &clip);
            } else {
                SDL_SetRenderClipRect(renderer, NULL);
            }
        }
    }
}

void microui_events(mu_Context *ctx, SDL_Event *event, SDL_Renderer *renderer)
{
    switch (event->type) {
    case SDL_EVENT_QUIT: exit(EXIT_SUCCESS); break;
    case SDL_EVENT_MOUSE_MOTION: {
        // mu_input_mousemove(ctx, event->motion.x, event->motion.y); break;
        float lx, ly;
        SDL_RenderCoordinatesFromWindow(renderer, event->motion.x, event->motion.y, &lx, &ly);
        mu_input_mousemove(ctx, (int)lx, (int)ly);
        break;
    }
    case SDL_EVENT_MOUSE_WHEEL: mu_input_scroll(ctx, 0, event->wheel.y * -30); break;
    case SDL_EVENT_TEXT_INPUT: mu_input_text(ctx, event->text.text); break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP: {
        // int b = button_map[event->button.button & 0xff];
        // if (b && event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) { mu_input_mousedown(ctx, event->button.x, event->button.y, b); }
        // if (b && event->type ==   SDL_EVENT_MOUSE_BUTTON_UP) { mu_input_mouseup(ctx, event->button.x, event->button.y, b);   }
        // break;
        float lx, ly;
        SDL_RenderCoordinatesFromWindow(renderer, event->button.x, event->button.y, &lx, &ly);
        int b = button_map[event->button.button & 0xff];
        if (b && event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) { mu_input_mousedown(ctx, (int)lx, (int)ly, b); }
        if (b && event->type == SDL_EVENT_MOUSE_BUTTON_UP)   { mu_input_mouseup(ctx,   (int)lx, (int)ly, b); }
        break;
    }

    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP: {
        int c = key_map[event->key.key & 0xff];
        if (c && event->type == SDL_EVENT_KEY_DOWN) { mu_input_keydown(ctx, c); }
        if (c && event->type ==   SDL_EVENT_KEY_UP) { mu_input_keyup(ctx, c);   }
        break;
    }
    }
}
