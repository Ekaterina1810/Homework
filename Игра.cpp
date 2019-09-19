#include "TXLib.h"
const float dt = 3;
int radius = 50;
const int childRadius = 10;
float childx = 100*(rand() % 5);
float childy = 100*(rand() % 5);

void drawBall(float x, float y, int radius)
{
    txSetFillColor(RGB(0,255,0));
    txSetColor(RGB(0,100,0));
    txCircle(x,y,radius);
    txSetFillColor(RGB(0,15,0));
}

void unDrawBall(float x, float y, float vx, float vy, float dt)
{

    if (x < 0 || x > 800)
        vy = -vy;
    if (y < 0 || y > 600)
        vx = -vx;
    x += vx * dt;
    y += vy * dt;

    txSetFillColor(RGB(0,0,0));
    txSetColor(RGB(0,0,0));
    txCircle(x,y,radius);
}


void moveBall(float x, float y, float vx, float vy, float dt)
{

     if (x < 0 || x > 800)
           vy = -vy;
     if (y < 0 || y > 600)
           vx = -vx;
     x += vx * dt;
     y += vy * dt;

     drawBall(x, y, radius);
}

void reDrawChildBall ()
{
    unDrawBall(childx, childy, 0, 0, 0);
    childx = 100*(1 + rand() % 7);
    childy = 100*(1 + rand() % 5);
    drawBall (childx,childy,childRadius);
}

bool checkPosition (float x, float y, float vx, float vy, float dt)
{
    if (x < 0 || x > 800)
        vy = -vy;
    if (y < 0 || y > 600)
        vx = -vx;
    x += vx * dt;
    y += vy * dt;
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

    float x=400;
    float y=300;
    float vx=10;
    float vy=10;


    drawBall (childx,childy,childRadius);

    for (;;)
    {
        if (GetAsyncKeyState(VK_SPACE))  {
            exit(0);
            return 0;
        }


        unDrawBall(x, y, vx, vy, dt);

        if (GetAsyncKeyState(VK_LEFT))
            vx -= 3;

        if (GetAsyncKeyState(VK_RIGHT))
            vx += 3;

        if (GetAsyncKeyState(VK_UP))
            vy -= 3;

        if (GetAsyncKeyState(VK_DOWN))
            vy += 3;

        if (checkPosition(x, y, vx, vy, dt))
        {
            radius = radius + childRadius;

            if (radius > 100)
            {
                unDrawBall(childx, childy, 0, 0, 0);
                printf("%s \n", "Game over");
                exit(0);
                return 0;
            }
            reDrawChildBall();
        }
        moveBall(x, y, vx, vy, dt);

        txSleep(dt);
    }

    txDestroyWindow();
    return 0;
}
