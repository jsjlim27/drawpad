#include "drawpad.h"

void init_DrawPadStates(struct DrawPadStates *AppStates) 
{
        AppStates->brushSize = DEFAULT_BRUSH_SIZE;
        AppStates->cleanCanvas = false;
        AppStates->bgColor = INIT_COLOR(DEFAULT_BG_COLOR);
        AppStates->brushColor = INIT_COLOR(DEFAULT_BRUSH_COLOR);

        AppStates->data = NULL;
        AppStates->aux = NULL;
        AppStates->dataLength = 0;
        AppStates->auxLength = 0;
}

void clean_canvas(struct DrawPadStates *AppStates)
{
        AppStates->cleanCanvas = true;
}

void update_brush_size(int size, struct DrawPadStates *AppStates)
{
        AppStates->brushSize = 
                AppStates->brushSize + size * BRUSH_SIZE_CHANGE_FACTOR;

        if (AppStates->brushSize < MIN_BRUSH_SIZE)
                AppStates->brushSize = MIN_BRUSH_SIZE;
}
