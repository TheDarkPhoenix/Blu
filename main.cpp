/*
    Author: Maciej Stêpieñ
    Copyright(c) 2013 Maciej Stêpieñ
    Version: pre-beta
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "car.h"
#include "terrain.h"
#include "game.h"
#include <cstdio>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480, 32), "Hill Racing", sf::Style::Close);
    window.SetFramerateLimit(70);
    Game gra;
    gra.Menu(window);
    return 0;
}
