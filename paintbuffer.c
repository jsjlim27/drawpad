#include "drawpad.h"

#define BUF_SIZE 4096 

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
		AppStates->data = rear;
		AppStates->dataLength = front - rear;
        }
        else if (front < rear)
        {
		AppStates->data = Specks;
		AppStates->dataLength = front - Specks;
		AppStates->aux = rear;
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
