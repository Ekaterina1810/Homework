#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


using namespace sf;
using namespace std;

char s[5];
int len = 0;
int cpos = 0;
string full_text;
sf::Font font;
sf::Text my_text;

int kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}



int main()
{
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    sf::CircleShape shape(15);
    shape.setFillColor(sf::Color(100, 250, 250));

    std::fstream my_file ("main.cpp");

    if (!my_file.is_open())
        return EXIT_FAILURE;

    my_file.seekg(0, my_file.end);
    len = my_file.tellg();

    if(!font.loadFromFile("arial.ttf"))
        cout << "font is not loaded" << endl;

    my_text.setFont(font);
    my_text.setColor(sf::Color::Green);
    my_text.setCharacterSize(10);

    while (app.isOpen())
    {

        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed) {

                if (cpos < len) {

                    app.clear();
                    my_file.seekg(cpos,my_file.beg);
                    my_file.read(s, 5);
                    cpos += 5;
                    full_text += s;
                    my_text.setString(full_text);
                    app.draw(my_text);
                    app.display();
                }
                else {
                    return EXIT_SUCCESS;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
