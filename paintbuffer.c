#include "drawpad.h"

#define BUF_SIZE 4096 
// #define INTERP_SIZE 2048

// static SDL_Rect Specks[BUF_SIZE * (1 + INTERP_SIZE)];
static SDL_Rect Specks[BUF_SIZE];

static SDL_Rect *rear = Specks; 
static SDL_Rect *front = Specks;

void store_paint(int x, int y, 
		 struct DrawPadStates *AppStates) 
{ 
        if (front > Specks + BUF_SIZE - 1)
                front = Specks;

        front->x = x; 
        front->y = y;
	front->w = AppStates->brushSize;
	front->h = AppStates->brushSize;

        front++;
}

void retrieve_paint(struct DrawPadStates *AppStates)
{
        if (front > rear)
        {
                // *data = rear;
		AppStates->data = rear;

                // *n_data = front - rear;
		AppStates->dataLength = front - rear;
        }
        else if (front < rear)
        {
                // *data = Specks;
		AppStates->data = Specks;

                // *n_data = front - Specks;
		AppStates->dataLength = front - Specks;

                // *data_extra = rear;
		AppStates->aux = rear;

                // *n_data_extra = Specks + BUF_SIZE - rear;
		AppStates->auxLength = Specks + BUF_SIZE - rear;
        }
	else // (front == rear)
	{
		AppStates->data = NULL;
		AppStates->aux = NULL;
		AppStates->dataLength = 0;
		AppStates->auxLength = 0;
	}

        rear = front;
}

// how to implement undo feature? 
// just "rewind" the Specks to previous "stroke"
// as you traverse backwards the stroke region of the Specks,
// set the alpha value of each Rect element to zero!
// this approach might be buggy when there are Rect objects under the same coordinates.
