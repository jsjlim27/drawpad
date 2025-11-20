#include "drawpad.h"

static SDL_Rect *dataRecv = NULL;
static SDL_Rect *auxRecv = NULL;
static int dataRecvLength = 0;
static int auxRecvLength = 0;

static void render_texture(SDL_Renderer **rend, SDL_Texture **tex);
static void render_blank_canvas(SDL_Renderer **rend, SDL_Texture **tex);
static bool frame_has_data_to_draw();
static bool data_is_split();

void render_frame(SDL_Renderer **rend, SDL_Texture **tex)
{
        retrieve_paint(&dataRecv, &dataRecvLength,
                       &auxRecv, &auxRecvLength);

        if ( frame_has_data_to_draw() )
                render_texture(rend, tex);

        if ( get_clean_canvas() )
                render_blank_canvas(rend, tex);

        SDL_SetRenderDrawColor(*rend,
                               get_bg_red(),
                               get_bg_green(),
                               get_bg_blue(), 255);

        SDL_RenderClear(*rend);
        SDL_RenderCopy(*rend, *tex, NULL, NULL);

        SDL_RenderPresent(*rend);

        // delay before starting next frame
        SDL_Delay(FRAME_DELAY);
}

static void render_texture(SDL_Renderer **rend, SDL_Texture **tex)
{
        // start rendering to texture:
        SDL_SetRenderTarget(*rend, *tex);

        SDL_SetRenderDrawColor(*rend,
                               get_brush_red(), 
                               get_brush_green(), 
                               get_brush_blue(), 255);

        SDL_RenderDrawRects(*rend, 
                            dataRecv, dataRecvLength);
        SDL_RenderFillRects(*rend, 
                            dataRecv, dataRecvLength);

        if ( data_is_split() )
        {
                SDL_RenderDrawRects(*rend, 
                                    auxRecv,
                                    auxRecvLength);
                SDL_RenderFillRects(*rend, 
                                    auxRecv, 
                                    auxRecvLength);
        }
        // set render target back to window:
        SDL_SetRenderTarget(*rend, NULL);
}

static void render_blank_canvas(SDL_Renderer **rend, SDL_Texture **tex)
{
        SDL_SetRenderTarget(*rend, *tex);

        SDL_SetRenderDrawColor(*rend, 
                               get_bg_red(),
                               get_bg_green(),
                               get_bg_blue(), 255);

        SDL_RenderClear(*rend);
        SDL_SetRenderTarget(*rend, NULL);

        cleaned_canvas();
}

static bool frame_has_data_to_draw()
{
        return dataRecv != NULL 
                || auxRecv != NULL 
                 || dataRecvLength != 0 
                  || auxRecvLength != 0;
}

static bool data_is_split()
{
        return auxRecv != NULL && auxRecvLength > 0;
}
