#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
using namespace sf;

const float dt = 1;
const int maxX = 1000;
const int maxY = 800;
float vx=0;
float vy=0;
const int radius = 2;
const int maxCircles = 200;
//size of ball should be les to have large number of balls, if ball is too big it will not be enough space to generate requested number op balls.
Vector2f vel = Vector2f(1+rand() %  5, 1+rand() % 5);

struct ball {
    Vector2f center;
    Vector2f velocity = vel;
    int goRight = 1; //direction right, if -1, direction left - needed for wall collision
    int goDown = 1;//direction down, if -1, direction up - needed for wall collision
    int radius;
};

struct ball ballsArray[maxCircles];

//generates initial ball's center coordinates to avoid their overlapping
Vector2f genCoors ()
{
    bool noReGen = true;
    float x;
    float y;
    for (;;)
    {
        noReGen = true;
        x = radius + 1 + 100*(rand() % 10) + 10*(rand() % 9) + rand() % 9;
        y = radius + 1 + 100*(rand() % 8) + 10*(rand() % 9) + rand() % 9;
        if (x < (maxX - radius))
        {
           if (y < (maxY - radius- 50))
           {
                int tempj = 0;
                for (int j = 0; j < maxCircles; j ++)
                {
                    ball oldCoors = ballsArray[j];
                    if (abs(x - oldCoors.center.x) < radius)
                    {
                        noReGen = false;
                        tempj = j;
                        j = maxCircles;
                    }

                    if (abs(y - oldCoors.center.y) < radius)
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
    Vector2f pos = Vector2f(x, y);
    return pos;
}

int main()
{
    sf::RenderWindow app(sf::VideoMode(maxX, maxY), "SFML window");

    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color(100, 250, 250));
    //define initial ball coordinates
    for (int i = 0; i < maxCircles;i++ )
    {
        ballsArray[i].center = genCoors();
    }

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        app.clear();

        for (int i = 1 ; i < maxCircles; i++)
        {
            //trying to catch collision
            bool changed = false;
            for (int tempi = 0; tempi < maxCircles; tempi++)
            {
                if (!changed)
                {
                    if (i!=tempi)
                    {
                        ball ball1 = ballsArray[i];
                        ball ball2 = ballsArray[tempi];
                        if (abs(ball1.center.x - ball2.center.x) < 3*radius)
                        {
                            if (abs(ball1.center.y - ball2.center.y) < 3*radius)
                            {
                                if (ball1.velocity.x > 0)
                                {
                                    if ((ball1.velocity.x + ball2.velocity.x) > ball1.velocity.x)
                                    {
                                        //both balls go right
                                        changed = true;
                                        ball1.velocity.y = -ball1.velocity.y;
                                        ball2.velocity.y = -ball2.velocity.y;
                                    }
                                    else if ((ball1.velocity.y + ball2.velocity.y) > ball1.velocity.y)
                                    {
                                        //both balls go down
                                        changed =true;
                                        ball1.velocity.x = -ball1.velocity.x;
                                        ball2.velocity.x = -ball2.velocity.x;
                                    }
                                    else
                                    {
                                        //balls are going towards each other
                                        changed = true;
                                        ball1.velocity.x = -ball1.velocity.x;
                                        ball1.velocity.y = -ball1.velocity.y;
                                        ball2.velocity.x = -ball2.velocity.x;
                                        ball2.velocity.y = -ball2.velocity.y;
                                    }
                                }
                                else
                                {
                                    if ((abs(ball1.velocity.x) + ball2.velocity.x) < abs(ball1.velocity.x))
                                    {
                                        // both balls go left
                                        changed = true;
                                        ball1.velocity.y = -ball1.velocity.y;
                                        ball2.velocity.y = -ball2.velocity.y;
                                    }
                                    else if ((ball1.velocity.y + ball2.velocity.y) > ball1.velocity.y)
                                    {
                                        //both balls go down
                                        changed =true;
                                        ball1.velocity.x = -ball1.velocity.x;
                                        ball2.velocity.x = -ball2.velocity.x;
                                    }
                                    else
                                    {
                                        //balls are going towards each other
                                        changed = true;
                                        ball1.velocity.x = -ball1.velocity.x;
                                        ball1.velocity.y = -ball1.velocity.y;
                                        ball2.velocity.x = -ball2.velocity.x;
                                        ball2.velocity.y = -ball2.velocity.y;
                                    }
                                }

                            }
                        }
                    }
                }
            }
            Vector2f pos = ballsArray[i].center;
            if ((pos.x + ballsArray[i].velocity.x * ballsArray[i].goRight) < (maxX - vel.x - ballsArray[i].radius - 100))
            {
                if ((pos.x + ballsArray[i].velocity.x * ballsArray[i].goRight) < (vel.x + ballsArray[i].radius))
                {
                    ballsArray[i].goRight = 1;
                }

                pos.x = pos.x + ballsArray[i].velocity.x * ballsArray[i].goRight;
            }
            else
            {
                ballsArray[i].goRight = -1;
                pos.x = pos.x + ballsArray[i].velocity.x * ballsArray[i].goRight;

            }
            if ((pos.y + ballsArray[i].velocity.y * ballsArray[i].goDown) < (maxY - vel.y - ballsArray[i].radius - 100))
            {
                if ((pos.y + ballsArray[i].velocity.y * ballsArray[i].goDown) < (vel.y + ballsArray[i].radius))
                {
                    ballsArray[i].goDown = 1;
                }

                pos.y = pos.y + ballsArray[i].velocity.y * ballsArray[i].goDown;
            }
            else
            {
                ballsArray[i].goDown = -1;
                pos.y = pos.y + ballsArray[i].velocity.y * ballsArray[i].goDown;
            }
            ballsArray[i].center = pos;

            //changed = true;
            for (int tempi = 0; tempi < maxCircles; tempi++)
            {
                //if (changed)
                //{
                    if (i!=tempi)
                    {
                        ball ball1 = ballsArray[i];
                        ball ball2 = ballsArray[tempi];
                        if (abs(ball1.center.x - ball2.center.x) < 2 * radius)
                        {
              //              changed = false;
                            if (abs(ball1.center.y - ball2.center.y) < 2 * radius)
                            {
                                if (ball1.center.x > ball2.center.x)
                                {
                                    ball1.center.x = ball1.center.x + radius;
                                }
                                else
                                {
                                    ball1.center.x = ball1.center.x - radius;
                                }
                                if (ball1.center.y > ball2.center.y)
                                {
                                    ball1.center.y = ball1.center.y + radius;
                                }
                                else
                                {
                                     ball1.center.y = ball1.center.y - radius;
                                }

                                ballsArray[i] = ball1;
                            }
                        }

                    }
                //}
            }



            shape.setPosition(ballsArray[i].center);
            app.draw(shape);
        }
        app.display();
        sf::Time time = sf::seconds(dt);
        sleep(time);
    }

    return EXIT_SUCCESS;
}

