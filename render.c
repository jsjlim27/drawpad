#include "drawpad.h"

static struct SDL_Rect cursor;

void render_frame(SDL_Renderer **rend, SDL_Texture **tex,
                  struct DrawPadStates *AppStates);

static void render_texture(SDL_Renderer **rend, SDL_Texture **tex,
                           struct DrawPadStates *AppStates);

static void render_blank_canvas(SDL_Renderer **rend, SDL_Texture **tex,
                                struct DrawPadStates *AppStates);

static bool frame_has_data_to_draw(const struct DrawPadStates *AppStates);
static bool data_is_split(const struct DrawPadStates *AppStates);

void render_frame(SDL_Renderer **rend, SDL_Texture **tex,
                  struct DrawPadStates *AppStates)
{
        retrieve_paint(AppStates);

        if ( frame_has_data_to_draw(AppStates) )
                render_texture(rend, tex, AppStates);

        if (AppStates->cleanCanvas)
                render_blank_canvas(rend, tex, AppStates);

        SDL_SetRenderDrawColor( *rend, COLOR(AppStates->bgColor) );
        SDL_RenderClear(*rend);
        SDL_RenderCopy(*rend, *tex, NULL, NULL);

        SDL_RenderPresent(*rend);

        // delay before starting next frame
        SDL_Delay(FRAME_DELAY);
}

static void render_texture(SDL_Renderer **rend, SDL_Texture **tex,
                           struct DrawPadStates *AppStates)
{
        // start rendering to texture:
        SDL_SetRenderTarget(*rend, *tex);

        SDL_SetRenderDrawColor(*rend, COLOR(AppStates->brushColor));

        SDL_RenderDrawRects(*rend, 
                            AppStates->data, AppStates->dataLength);
        SDL_RenderFillRects(*rend, 
                            AppStates->data, AppStates->dataLength);

        if ( data_is_split(AppStates) )
        {
                SDL_RenderDrawRects(*rend, 
                                    AppStates->aux, 
                                    AppStates->auxLength);
                SDL_RenderFillRects(*rend, 
                                    AppStates->aux, 
                                    AppStates->auxLength);
        }
        // set render target back to window:
        SDL_SetRenderTarget(*rend, NULL);
}

static void render_blank_canvas(SDL_Renderer **rend, SDL_Texture **tex,
                                struct DrawPadStates *AppStates)
{
        SDL_SetRenderTarget(*rend, *tex);
        SDL_SetRenderDrawColor(*rend, COLOR(AppStates->bgColor));
        SDL_RenderClear(*rend);
        SDL_SetRenderTarget(*rend, NULL);

        AppStates->cleanCanvas = false;
}

static bool frame_has_data_to_draw(const struct DrawPadStates *AppStates)
{
        return AppStates->data != NULL || AppStates->aux != NULL 
                || AppStates->dataLength != 0 || AppStates->auxLength != 0;
}

static bool data_is_split(const struct DrawPadStates *AppStates)
{
        return AppStates->aux != NULL && AppStates->auxLength > 0;
}
