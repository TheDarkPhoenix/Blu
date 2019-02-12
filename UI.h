#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include "point.h"
#include "UIObject.h"

class UI
{
    private:
        pt::Point<float> pWymiary;
        static const int nMinOdl = 10;
        static const int nMinWym = 50;
        static const int nMaxWym = 300;
        static const int nMinOdlUpDown = 50;
        static const int nMinOdlLeftRight = 50;
        int nOdlUpDown;
        float fWymiary1x1;
        UIObject ** objects;
        int nAktualny;
        sf::Color* backcol;
        sf::Sprite* backimg;
        int ilosc;
        pt::Point<float> pPozycja;
        bool aEkran [4][25];
        int nWiersz;
        int nKolumna;
        int ostSize;

    public:
        UI(pt::Point<float> pWymiaryOkna, int nIlosc);
        UI(pt::Point<float> pWymiaryOkna, const sf::Color background, int nIlosc);
        UI(pt::Point<float> pWymiaryOkna, const sf::Image& background, int nIlosc);

        void AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col);
        void AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col, sf::Image& icon);
        void AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col, std::string str2);
        void AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col, int nKtory);
        void AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col, sf::Image& icon, int nKtory);
        int ShowUI(sf::RenderWindow& window);
};

#endif
