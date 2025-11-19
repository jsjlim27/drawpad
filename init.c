#include "drawpad.h"

bool init_SDL(SDL_Window **win, SDL_Renderer **rend, SDL_Texture **tex)
{
        int displayIndex;
        SDL_DisplayMode displayMode;

        if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
                return false;

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

        if ( SDL_GetCurrentDisplayMode(displayIndex, &displayMode) != 0 )
                return false;

        SDL_SetWindowSize(*win,
                          displayMode.w - displayMode.w / 4, 
                          displayMode.h - displayMode.h / 4);

        *rend = SDL_CreateRenderer(*win, 
                                   -1, 
                                   SDL_RENDERER_TARGETTEXTURE 
                                    | SDL_RENDERER_ACCELERATED);

        if (*rend == NULL)
                return false;

        *tex = SDL_CreateTexture(*rend,
                                 SDL_PIXELFORMAT_RGBA32,
                                 SDL_TEXTUREACCESS_TARGET,
                                 displayMode.w - displayMode.w / 4, 
                                 displayMode.h - displayMode.h / 4);

        if (*tex == NULL)
                return false;

        return true;
}
