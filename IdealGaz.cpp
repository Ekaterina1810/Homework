#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

const float dt = 1;
const int maxX = 800;
const int maxY = 600;
const int radius = 4;
const int maxCircles = 100;
//size of ball should be les to have large number of balls, if ball is too big it will not be enough space to generate requested number op balls.
Vector2f vel = Vector2f(3+rand() %  5, 5+rand() % 5);

struct ball {
    Vector2f center;
    Vector2f velocity = vel;
    int rad = radius;
    bool collided = false;
};

struct two_ball_plus_flag {
    ball ball1;
    ball ball2;
    bool flag;
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
                for (int j = 0; j < maxCircles; j ++)
                {
                    ball oldCoors = ballsArray[j];
                    if (abs(x - oldCoors.center.x) < radius)
                    {
                        noReGen = false;
                        j = maxCircles;
                    }
                    if (abs(y - oldCoors.center.y) < radius)
                    {
                        noReGen = false;
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

Vector2f genVelocity(int i)
{
    Vector2f newVelocityVector = ballsArray[i].velocity;
    if ((i % 5) == 1)
        newVelocityVector = - newVelocityVector;
    if ((i % 5) == 2)
        newVelocityVector.x = - newVelocityVector.x;
    if ((i % 5) == 3)
        newVelocityVector.y = - newVelocityVector.y;
    return newVelocityVector;
}

float abs_diff(float one, float second)
{
    return abs(one - second);
}

ball move_ball(ball checking_ball)
{
    Vector2f pos = checking_ball.center;
    if ((pos.x + checking_ball.velocity.x) < (maxX - 5 - checking_ball.velocity.x - checking_ball.rad))
    {
        if ((pos.x + checking_ball.velocity.x) < checking_ball.rad)
        {
            checking_ball.velocity.x = - checking_ball.velocity.x;
        }
        pos.x = pos.x + checking_ball.velocity.x;
    }
    else
    {
        checking_ball.velocity.x = - checking_ball.velocity.x;
        pos.x = pos.x + checking_ball.velocity.x;
    }
    if ((pos.y + checking_ball.velocity.y) < (maxY - 5 - checking_ball.velocity.y - checking_ball.rad))
    {
        if ((pos.y + checking_ball.velocity.y) < checking_ball.rad)
        {
            checking_ball.velocity.y = - checking_ball.velocity.y;
        }
        pos.y = pos.y + checking_ball.velocity.y;
    }
    else
    {
        checking_ball.velocity.y = - checking_ball.velocity.y;
        pos.y = pos.y + checking_ball.velocity.y;
    }
    checking_ball.center = pos;
    //re-check
    if (checking_ball.center.y > maxY - 5 - checking_ball.rad)
    {
        checking_ball.center.y = checking_ball.center.y - 2*abs(checking_ball.velocity.y);
    }
    if (checking_ball.center.x > maxX - 5 - checking_ball.rad)
    {
        checking_ball.center.x = checking_ball.center.x - 2*abs(checking_ball.velocity.x);
    }
    if (checking_ball.center.y < checking_ball.rad)
    {
        checking_ball.center.y = checking_ball.center.y + 2*abs(checking_ball.velocity.y);
    }
    if (checking_ball.center.x < checking_ball.rad)
    {
        checking_ball.center.x = checking_ball.center.x + 2*abs(checking_ball.velocity.x);
    }
    return checking_ball;
}

two_ball_plus_flag collision(ball ball1, ball ball2)
{
    bool changed = false;
    if (abs_diff(ball1.center.x, ball2.center.x) < 3*ball2.rad)
    {
        if (abs_diff(ball1.center.y, ball2.center.y) < 3*ball2.rad)
        {
            if (ball1.velocity.x == ball2.velocity.x)
            {
                //both balls go left or right
                changed = true;
                ball1.velocity.y = -ball1.velocity.y;
                ball2.velocity.y = -ball2.velocity.y;
                ball1.collided = true;
                ball2.collided = true;
                if (ball1.velocity.y == ball2.velocity.y)
                {
                    //balls go somewhere together
                    ball1.velocity.x = -ball1.velocity.x;
                }
            }
            else if (ball1.velocity.y == ball2.velocity.y)
            {
                //both balls go down or up
                changed = true;
                ball1.velocity.x = -ball1.velocity.x;
                ball2.velocity.x = -ball2.velocity.x;
                ball1.collided = true;
                ball2.collided = true;
                if (ball1.velocity.x == ball2.velocity.x)
                {
                    //balls go somewhere together
                    ball1.velocity.y = -ball1.velocity.y;
                }
            }
            else
            {
                //balls are going towards each other
                changed = true;
                ball1.velocity.x = -ball1.velocity.x;
                ball1.velocity.y = -ball1.velocity.y;
                ball2.velocity.x = -ball2.velocity.x;
                ball2.velocity.y = -ball2.velocity.y;
                ball1.collided = true;
                ball2.collided = true;
            }
        }
    }
    two_ball_plus_flag balls_flag;
    balls_flag.ball1 = ball1;
    balls_flag.ball2 = ball2;
    balls_flag.flag = changed;
    return balls_flag;
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
        ballsArray[i].velocity = genVelocity(i);
    }
    while (app.isOpen())
    {
        loop++;
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        app.clear();
        for (int i = 0 ; i < maxCircles; i++)
        {
            ballsArray[i].collided = false;
        }
        for (int i = 0 ; i < maxCircles; i++)
        {
            //trying to catch collision
            bool collide = false;
            for (int tempi = 0; tempi < maxCircles; tempi++)
            {
                if (i!=tempi)
                {
                    if(!ballsArray[i].collided)
                    {
                        if (!ballsArray[tempi].collided)
                        {
                            two_ball_plus_flag balls_plus_flag = collision (ballsArray[i], ballsArray[tempi]);
                            ballsArray[i] = balls_plus_flag.ball1;
                            ballsArray[tempi] = balls_plus_flag.ball2;
                            collide = balls_plus_flag.flag;
                            if (collide)
                            {
                                tempi = maxCircles;
                            }
                        }
                    }
                }
            }
            ballsArray[i] = move_ball(ballsArray[i]);
            shape.setPosition(ballsArray[i].center);
            app.draw(shape);
        }
        app.display();
        sf::Time time = sf::seconds(dt);
        sleep(time);
    }
    return EXIT_SUCCESS;
}

