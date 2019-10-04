#include "TXLib.h"
#include<iostream>
#include<iomanip>

const float dt = 300;
int radius = 5;
float vx=0;
float vy=0;
const int maxCircles = 100;

struct coors {
  float x;
  float y;
};

struct coors coorsArray[maxCircles];

void drawBall(coors circleCoors, int radius)
{
    txSetFillColor(RGB(0,255,0));
    txSetColor(RGB(0,100,0));
    txCircle(circleCoors.x,circleCoors.y,radius);
    txSetFillColor(RGB(0,15,0));
}

coors genCoors(coors coordinates)
{
    bool noReGen = true;
    for (;;)
    {
        noReGen = true;
        coordinates.x = radius + 1 + 100*(rand() % 10) + 10*(rand() % 9) + rand() % 9;
        coordinates.y = radius + 1 + 100*(rand() % 8) + 10*(rand() % 9) + rand() % 9;
        if (coordinates.x < (1000 - radius))
        {
            if (coordinates.y < (800 - radius))
            {
                int tempj = 0;
                for (int j = 1; j < maxCircles; j ++)
                {
                    coors oldCoors = coorsArray[j];
                    if (abs(coordinates.x - oldCoors.x) < radius)
                    {
                        noReGen = false;
                        tempj = j;
                        j = maxCircles;
                    }

                    if (abs(coordinates.y - oldCoors.y) < radius)
                    {
                        noReGen = false;
                        tempj = j;
                        j = maxCircles;
                    }
                }

                if (noReGen)
                {
                    break;
                }
            }
        }
    }
    return coordinates;
}

int main()
{
    coors coordinates;

    txCreateWindow(1000,800);

    for (;;)
    {
        txClear();

        if (GetAsyncKeyState(VK_SPACE))
        {
            exit(0);
            return 0;
        }

        for (int i = 1; i < maxCircles; i++)
        {
            coorsArray[i] = genCoors(coordinates);
            drawBall (coorsArray[i], radius);
        }

        txSleep(dt);
    }

    txDestroyWindow();
    return 0;
}
