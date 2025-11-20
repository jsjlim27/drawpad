#include "drawpad.h"

#define BUF_SIZE 4096 

static SDL_Rect specks[BUF_SIZE];
static SDL_Rect *rear = specks; 
static SDL_Rect *front = specks; 

void store_paint(int x, int y)
{ 
        if (front > specks + BUF_SIZE - 1)
                front = specks;

        front->x = x; 
        front->y = y;
        front->w = get_brush_size();
        front->h = get_brush_size();

        front++;
}

void retrieve_paint(SDL_Rect **dataSend, int *dataSendLength,
                    SDL_Rect **auxSend,  int *auxSendLength)
{
        // returning data is in a single contiguous region of specks[].
        if (front > rear)
        {
                *dataSend = rear;
                *auxSend = NULL;

                *dataSendLength = front - rear;
                *auxSendLength = 0;
        }
        // returning data is divided among two contiguous regions of specks[].
        else if (front < rear)
        {
                *dataSend = specks;
                *auxSend = rear;

                *dataSendLength = front - specks;
                *auxSendLength = specks + BUF_SIZE - rear;
        }
        else // (front == rear)
        {
                *dataSend = NULL;
                *auxSend = NULL;

                *dataSendLength = 0;
                *auxSendLength = 0;
        }
        rear = front;
}
