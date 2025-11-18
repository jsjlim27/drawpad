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

struct DrawPadStates {
	int brushSize;
	bool cleanCanvas;
	SDL_Color bgColor;
	SDL_Color brushColor;

	SDL_Rect *data;
	SDL_Rect *aux;
	int dataLength;
	int auxLength;
};

/********************************* init.c ************************************/
bool init_SDL(SDL_Window **win, SDL_Renderer **rend, SDL_Texture **tex);

/********************************* states.c **********************************/
void init_DrawPadStates(struct DrawPadStates *AppStates);
void clean_canvas(struct DrawPadStates *AppStates);
void update_brush_size(int size, struct DrawPadStates *AppStates);

/******************************* paintbuffer.c *******************************/
void store_paint(int x, int y, struct DrawPadStates *AppStates);
void retrieve_paint(struct DrawPadStates *AppStates);

/******************************* render.c ************************************/
void render_frame(SDL_Renderer **rend, SDL_Texture **tex,
		  struct DrawPadStates *AppStates);
