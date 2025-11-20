#include "SDL.h"
#include <stdbool.h>

#define FRAME_DELAY 1.66

#define DEFAULT_BRUSH_SIZE 10
#define BRUSH_SIZE_CHANGE_FACTOR 10
#define MIN_BRUSH_SIZE 10

#define BLACK  0, 0, 0, 255
#define LIGHT_GREEN  199, 242, 204, 255
#define BLUE 79, 200, 239, 255

#define DEFAULT_BG_COLOR BLACK
#define DEFAULT_BRUSH_COLOR BLUE

#define COLOR(color) color.r, color.g, color.b, color.a
#define INIT_COLOR(color) (SDL_Color){color}

/********************************* init.c ************************************/
bool init_SDL(SDL_Window **win, SDL_Renderer **rend, SDL_Texture **tex,
              SDL_Cursor **cursor);

/********************************* states.c **********************************/
void update_brush_size(int size);

void need_clean_canvas();
void cleaned_canvas();

int get_brush_size();

int get_bg_red();
int get_bg_green();
int get_bg_blue();

int get_brush_red();
int get_brush_green();
int get_brush_blue();

bool get_clean_canvas();

/******************************* paintbuffer.c *******************************/
void store_paint(int x, int y);
void retrieve_paint(SDL_Rect **dataSend, int *dataSendLength, 
                    SDL_Rect **auxSend, int *auxSendLength);

/******************************* render.c ************************************/
void render_frame(SDL_Renderer **rend, SDL_Texture **tex);
