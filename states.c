#include "drawpad.h"

struct DrawPadStates {
        int brushSize;
        bool cleanCanvas;
        SDL_Color bgColor;
        SDL_Color brushColor;
};

static struct DrawPadStates states = {
        .brushSize = DEFAULT_BRUSH_SIZE,
        .cleanCanvas = false,
        .bgColor = INIT_COLOR(DEFAULT_BG_COLOR),
        .brushColor = INIT_COLOR(DEFAULT_BRUSH_COLOR)
};

void update_brush_size(int size)
{
        states.brushSize = 
                states.brushSize + size * BRUSH_SIZE_CHANGE_FACTOR;

        if (states.brushSize < MIN_BRUSH_SIZE)
                states.brushSize = MIN_BRUSH_SIZE;
}

void need_clean_canvas() { states.cleanCanvas = true; }
void cleaned_canvas() { states.cleanCanvas = false; }

int get_brush_size() { return states.brushSize; }

int get_bg_red() { return states.bgColor.r; }
int get_bg_green() { return states.bgColor.g; }
int get_bg_blue() { return states.bgColor.b; }

int get_brush_red() { return states.brushColor.r; }
int get_brush_green() { return states.brushColor.g; }
int get_brush_blue() { return states.brushColor.b; }

bool get_clean_canvas() { return states.cleanCanvas; }
