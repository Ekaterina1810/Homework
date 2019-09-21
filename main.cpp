#include "TXLib.h"
const float dt = 50;
bool move = false;
int radius = 50;
const int childRadius = 10;
float childx = 100*(rand() % 5);
float childy = 100*(rand() % 5);
float x=400;
float y=300;
float vx=0;
float vy=0;

void drawBall(float x, float y, int radius)
{
    txSetFillColor(RGB(0,255,0));
    txSetColor(RGB(0,100,0));
    txCircle(x,y,radius);
    txSetFillColor(RGB(0,15,0));
}

void moveBall(float vx, float vy, float dt)
{
    if (x < 0 || x > 800)
        vy = -vy;
    if (y < 0 || y > 600)
        vx = -vx;
    x += vx * dt;
    y += vy * dt;
}

bool checkPosition()
{

    if (abs(x - childx) < (radius + childRadius) && abs(y - childy) < (radius + childRadius))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int main()
{
    txCreateWindow(800,600);


    drawBall (childx,childy,childRadius);
    drawBall (x, y, radius);

    for (;;)
    {
        move = false;

        if (GetAsyncKeyState(VK_SPACE))
        {
            exit(0);
            return 0;
        }


        if (GetAsyncKeyState(VK_LEFT))
        {
            vx = -0.1;
            vy = 0;
            move = true;
        }

        if (GetAsyncKeyState(VK_RIGHT))
        {
            vx = 0.1;
            vy = 0;
            move = true;
        }

        if (GetAsyncKeyState(VK_UP))
        {
            vy = -0.1;
            vx = 0;
            move = true;
        }

        if (GetAsyncKeyState(VK_DOWN))
        {
            vy = 0.1;
            vx = 0;
            move = true;
        }

        if (move)
        {

            if (checkPosition())
            {
                radius = radius + childRadius;

                if (radius > 100)
                {
                    txClear();
                    drawBall(x, y, radius);
                    printf("%s \n", "Game over");
                    exit(0);
                    return 0;
                }

                childx = 100*(1 + rand() % 7);
                childy = 100*(1 + rand() % 5);
            }
            //txClear erases everything, need to draw two balls again
            txClear();
            drawBall (childx,childy,childRadius);
            moveBall(vx, vy, dt);
            drawBall(x, y, radius);
        }

        txSleep(dt);
    }

    txDestroyWindow();
    return 0;
}
