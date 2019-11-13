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
int ccpos = 0;
string full_text;
sf::Font font;
sf::Text my_text;
int maxLines = 50;
int maxX = 800;
int maxY = 600;

int main()
{
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    std::fstream my_file ("main.cpp");
    if (!my_file.is_open())
        return EXIT_FAILURE;
    my_file.seekg(0, my_file.end);
    len = my_file.tellg();
    char all_text[len];
    my_file.seekg(0,my_file.beg);
    my_file.read(all_text, len);
    my_file.close();
    if(!font.loadFromFile("arial.ttf"))
    {
        cout << "font is not loaded" << endl;
        return EXIT_FAILURE;
    }
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
                    //my_file.seekg(cpos,my_file.beg);
                    //my_file.read(s, 5);
                    for (int i = cpos; i<(cpos+5); i++)
                    {
                        full_text += all_text[i];
                    }
                    cpos += 5;
                    my_text.setString(full_text);
                    app.draw(my_text);
                    app.display();
                }
                else
                {
                    app.clear();
                    for (int i = ccpos; i<(ccpos+5); i++)
                    {
                        full_text += all_text[i];
                    }
                    int n_end_lines = 0;
                    for (int i =1; i < full_text.length(); i++)
                    {
                        if (full_text.substr(i,1) == '\n')
                        {
                            n_end_lines++;
                        }
                    }
                    ccpos += 5;
                    if (ccpos > len)
                        ccpos = 0;
                    if (n_end_lines > maxLines)
                    {
                        my_text.setPosition(0,-(n_end_lines-maxLines)*(maxY/maxLines));
                    }
                    my_text.setString(full_text);
                    app.draw(my_text);
                    app.display();
                }
            }
        }
    }
    my_file.close();
    return EXIT_SUCCESS;
}
