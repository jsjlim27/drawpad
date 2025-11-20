#include "drawpad.h"

int main(int argc, char **argv)
{ 
        SDL_Window *win;
        SDL_Renderer *rend;
        SDL_Texture *tex;
        SDL_Cursor *cursor;
        bool running;

        if ( !init_SDL(&win, &rend, &tex, &cursor) )
                return 1;
        running = true;

        while (running) {
                SDL_Event ev;
                while ( SDL_PollEvent(&ev) != 0 ) {
                        switch (ev.type) {
                                case SDL_QUIT:
                                        running = false;
                                        break;

                                case SDL_MOUSEWHEEL:
                                        update_brush_size(ev.wheel.y);
                                        break;

                                case SDL_MOUSEBUTTONDOWN:
                                        switch (ev.button.button) {
                                                case SDL_BUTTON_LEFT:
                                                        store_paint(
                                                                ev.button.x, 
                                                                ev.button.y
                                                        );
                                                        break;
                                                case SDL_BUTTON_X1:
                                                        need_clean_canvas();
                                                        break;
                                        }
                                        break;

                                case SDL_MOUSEMOTION:
                                        switch (ev.motion.state) {
                                                case SDL_BUTTON_LEFT:
                                                        store_paint(
                                                                ev.motion.x, 
                                                                ev.motion.y
                                                        );
                                                        break;
                                        }
                                        break;
                        }
                }
                render_frame(&rend, &tex);
        }

        SDL_FreeCursor(cursor);
        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();

        return 0;
}
