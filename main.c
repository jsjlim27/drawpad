#include "drawpad.h"
//#include <stdbool.h>

int main(int argc, char **argv)
{ 
        SDL_Window *win;
        SDL_Renderer *rend;
        SDL_Texture *tex;

        SDL_Surface *surf;
        SDL_Cursor *cursor;

        struct DrawPadStates AppStates;
        bool running;

        if ( !init_SDL(&win, &rend, &tex) )
                return 1;

        surf = SDL_LoadBMP("./sprites/brush.bmp");
        cursor = SDL_CreateColorCursor(surf, 0, 0);
        SDL_SetCursor(cursor);
        SDL_ShowCursor(SDL_ENABLE);

        init_DrawPadStates(&AppStates);
        running = true;

        while (running) {
                SDL_Event ev;
                while ( SDL_PollEvent(&ev) != 0 ) {
                        switch (ev.type) {
                                case SDL_QUIT:
                                        running = false;
                                        break;

                                case SDL_MOUSEWHEEL:
                                        update_brush_size(ev.wheel.y, &AppStates);
                                        break;

                                case SDL_MOUSEBUTTONDOWN:
                                        switch (ev.button.button) {
                                                case SDL_BUTTON_LEFT:
                                                        store_paint(ev.button.x, ev.button.y, &AppStates);
                                                        break;
                                                case SDL_BUTTON_X1:
                                                        clean_canvas(&AppStates);
                                                        break;
                                        }
                                        break;

                                case SDL_MOUSEMOTION:
                                        switch (ev.motion.state) {
                                                case SDL_BUTTON_LEFT:
                                                        store_paint(ev.motion.x, ev.motion.y, &AppStates);
                                                        break;
                                        }
                                        break;
                        }
                }
                render_frame(&rend, &tex, &AppStates);
        }

        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();

        return 0;
}
