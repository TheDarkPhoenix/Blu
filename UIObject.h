#ifndef UIOBJECT_H
#define UIOBJECT_H

#include <SFML/Graphics.hpp>
#include "point.h"

class UIObject
{
    private:
        pt::Point<float> pWymiary;
        pt::Point<float> pPozycja;
        sf::Shape sh;
        sf::String str;
        bool bImage;
        sf::Sprite * sImg;
        sf::Image * img;

    public:
        UIObject();
        UIObject(pt::Point<float> wymiary, pt::Point<float> pozycja, std::string str1, sf::Color cl);
        UIObject(pt::Point<float> wymiary, pt::Point<float> pozycja, std::string str1, sf::Color cl, sf::Image img1);
        UIObject(float wymiaryX, float wymiaryY, pt::Point<float> pozycja, std::string str1, sf::Color cl);
        UIObject(float wymiaryX, float wymiaryY, pt::Point<float> pozycja, std::string str1, sf::Color cl, sf::Image img1);
        bool ShowObject(sf::RenderWindow& window, const sf::Input& wejscie);
};

#endif
