#include "drawpad.h"

static bool init_window(SDL_Window **win);
static bool init_renderer(SDL_Renderer **rend, SDL_Window **win);
static bool init_texture(SDL_Texture **tex, SDL_Renderer **rend);
static bool init_cursor(SDL_Cursor **cursor);

bool init_SDL(SDL_Window **win, SDL_Renderer **rend, SDL_Texture **tex,
              SDL_Cursor **cursor)
{
        return SDL_Init(SDL_INIT_VIDEO) == 0
                && init_window(win)
                 && init_renderer(rend, win) 
                  && init_texture(tex, rend) 
                   && init_cursor(cursor);
}

static bool init_window(SDL_Window **win)
{
        int displayIndex;
        SDL_DisplayMode displayMode;

        *win = SDL_CreateWindow("drawpad", 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED,
                                800,
                                600,
                                SDL_WINDOW_BORDERLESS);
        if (*win == NULL)
                return false;

        displayIndex = SDL_GetWindowDisplayIndex(*win);

        if (displayIndex < 0)
                return false;

        if (SDL_GetCurrentDisplayMode(displayIndex, &displayMode) != 0)
                return false;

        SDL_SetWindowSize(*win,
                          displayMode.w - displayMode.w / 4, 
                          displayMode.h - displayMode.h / 4);

        return true;
}

static bool init_renderer(SDL_Renderer **rend, SDL_Window **win)
{
        *rend = SDL_CreateRenderer(*win, 
                                   -1, 
                                   SDL_RENDERER_TARGETTEXTURE 
                                   | SDL_RENDERER_ACCELERATED);
        if (*rend == NULL)
                return false;

        return true;
}

static bool init_texture(SDL_Texture **tex, SDL_Renderer **rend)
{
        int tex_width, tex_height;

        if ( SDL_GetRendererOutputSize(*rend, &tex_width, &tex_height) != 0 )
                return false;

        *tex = SDL_CreateTexture(*rend,
                                 SDL_PIXELFORMAT_RGBA32,
                                 SDL_TEXTUREACCESS_TARGET,
                                 tex_width, tex_height);
        if (*tex == NULL)
                return false;

        return true;
}

static bool init_cursor(SDL_Cursor **cursor)
{
        SDL_Surface *surf;

        surf = SDL_LoadBMP("sprites/brush.bmp");
        if (surf == NULL)
                return false;

        *cursor = SDL_CreateColorCursor(surf, 0, 0);
        SDL_FreeSurface(surf);

        if (*cursor == NULL)
                return false;

        SDL_SetCursor(*cursor);

        return true;
}
