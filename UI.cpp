#include "UI.h"
#include <iostream>

UI::UI(pt::Point<float> pWymiaryOkna, int nIlosc)
{
    pWymiary = pWymiaryOkna;
    objects = new UIObject*[nIlosc];
    if (pWymiary.x < pWymiary.y)
        fWymiary1x1 = (pWymiary.y - (3 * nMinOdl) - (2 * nMinOdlUpDown)) / 4;
    else
    {
        fWymiary1x1 = (pWymiary.x - (3 * nMinOdl) - (2 * nMinOdlLeftRight)) / 4;
        nOdlUpDown = (pWymiary.y - 3*fWymiary1x1 - 2*nMinOdl)/2;
    }
    if (fWymiary1x1 < nMinWym)
        fWymiary1x1 = nMinWym;
    nAktualny = 0;
    ilosc = nIlosc;
    pPozycja = pt::PointMake<float>(nMinOdlLeftRight, nOdlUpDown);
    backimg = 0;
    backcol = 0;
    nWiersz = 0;
    nKolumna = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 25; ++j)
            aEkran[i][j] = false;
    ostSize = 0;
}

UI::UI(pt::Point<float> pWymiaryOkna, const sf::Color background, int nIlosc)
{
    pWymiary = pWymiaryOkna;
    objects = new UIObject*[nIlosc];
    if (pWymiary.x < pWymiary.y)
        fWymiary1x1 = (pWymiary.y - (3 * nMinOdl) - (2 * nMinOdlUpDown)) / 4;
    else
    {
        fWymiary1x1 = (pWymiary.x - (3 * nMinOdl) - (2 * nMinOdlLeftRight)) / 4;
        nOdlUpDown = (pWymiary.y - 3*fWymiary1x1 - 2*nMinOdl)/2;
    }
    if (fWymiary1x1 < nMinWym)
        fWymiary1x1 = nMinWym;
    nAktualny = 0;
    backcol = new sf::Color(background);
    ilosc = nIlosc;
    pPozycja = pt::PointMake<float>(nMinOdlLeftRight, nOdlUpDown);
    backimg = 0;
    nWiersz = 0;
    nKolumna = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 25; ++j)
            aEkran[i][j] = false;
    ostSize = 0;
}

UI::UI(pt::Point<float> pWymiaryOkna, const sf::Image& background, int nIlosc)
{
    pWymiary = pWymiaryOkna;
    objects = new UIObject*[nIlosc];
    if (pWymiary.x < pWymiary.y)
        fWymiary1x1 = (pWymiary.y - (3 * nMinOdl) - (2 * nMinOdlUpDown)) / 4;
    else
    {
        fWymiary1x1 = (pWymiary.x - (3 * nMinOdl) - (2 * nMinOdlLeftRight)) / 4;
        nOdlUpDown = (pWymiary.y - 3*fWymiary1x1 - 2*nMinOdl)/2;
    }
    if (fWymiary1x1 < nMinWym)
        fWymiary1x1 = nMinWym;
    nAktualny = 0;
    backimg = new sf::Sprite;
    backimg->SetImage(background);
    ilosc = nIlosc;
    pPozycja = pt::PointMake<float>(nMinOdlLeftRight, nOdlUpDown);
    backcol = 0;
    nWiersz = 0;
    nKolumna = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 25; ++j)
            aEkran[i][j] = false;
    ostSize = 0;
}

void UI::AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col)
{
    bool bk;
    do
    {
        bk = false;
        for (int i = nKolumna; i < wymiary.x+nKolumna && i < 4; ++i)
            for(int j = nWiersz; j < wymiary.y+nWiersz && j < 25; ++j)
                if (aEkran[i][j] == true)
                {
                    bk = true;
                    if (nKolumna < 4)
                    {
                        ++nKolumna;
                        pPozycja.x += fWymiary1x1 + nMinOdl;
                    }
                    else
                    {
                        nKolumna = 0;
                        pPozycja.x = nMinOdlLeftRight;
                        ++nWiersz;
                        pPozycja.y += nMinOdl + fWymiary1x1;
                    }
                }
    }while(bk);
    if ((pPozycja.x + nMinOdl + fWymiary1x1 + nMinOdlLeftRight) > pWymiary.x && ostSize > 1)
    {
        pPozycja = pt::PointMake<float>(nMinOdlLeftRight, pPozycja.y + (fWymiary1x1 * wymiary.y) + nMinOdl);
        ++nWiersz;
        nKolumna = 0;
    }
    objects[nAktualny] = new UIObject(wymiary.x * fWymiary1x1 + (wymiary.x-1)*nMinOdl, wymiary.y * fWymiary1x1 + (wymiary.y-1)*nMinOdl, pPozycja, str, col);
    for (int i = nKolumna; i < wymiary.x+nKolumna && i < 4; ++i)
        for(int j = nWiersz; j < wymiary.y+nWiersz && j < 25; ++j)
            aEkran[i][j] = true;
    if ((pPozycja.x + nMinOdl + fWymiary1x1 + nMinOdlLeftRight) > pWymiary.x)
    {
        pPozycja = pt::PointMake<float>(nMinOdlLeftRight, pPozycja.y + (fWymiary1x1 * wymiary.y) + nMinOdl);
        ++nWiersz;
        nKolumna = 0;
    }
    else
    {
        pPozycja.x += wymiary.x * fWymiary1x1 + nMinOdl + (wymiary.x-1)*nMinOdl;
        nKolumna += wymiary.x;
    }
    ++nAktualny;
    ostSize = wymiary.x;
}

void UI::AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col, sf::Image& icon)
{
    bool bk;
    do
    {
        bk = false;
        for (int i = nKolumna; i < wymiary.x+nKolumna && i < 4; ++i)
            for(int j = nWiersz; j < wymiary.y+nWiersz && j < 25; ++j)
                if (aEkran[i][j] == true)
                {
                    bk = true;
                    if (nKolumna < 4)
                    {
                        ++nKolumna;
                        pPozycja.x += fWymiary1x1 + nMinOdl;
                    }
                    else
                    {
                        nKolumna = 0;
                        pPozycja.x = nMinOdlLeftRight;
                        ++nWiersz;
                        pPozycja.y += nMinOdl + fWymiary1x1;
                    }
                }
    }while(bk);

    if ((pPozycja.x + nMinOdl + fWymiary1x1 + nMinOdlLeftRight) > pWymiary.x  && ostSize > 1)
    {
        pPozycja = pt::PointMake<float>(nMinOdlLeftRight, pPozycja.y + fWymiary1x1 + nMinOdl);
        ++nWiersz;
        nKolumna = 0;
    }
    objects[nAktualny] = new UIObject(wymiary.x * fWymiary1x1 + (wymiary.x-1)*nMinOdl, wymiary.y * fWymiary1x1 + (wymiary.y-1)*nMinOdl, pPozycja, str, col, icon);
    for (int i = nKolumna; i < wymiary.x+nKolumna && i < 4; ++i)
        for(int j = nWiersz; j < wymiary.y+nWiersz && j < 25; ++j)
            aEkran[i][j] = true;

    if ((pPozycja.x + nMinOdl + fWymiary1x1 + nMinOdlLeftRight) > pWymiary.x)
    {
        pPozycja = pt::PointMake<float>(nMinOdlLeftRight, pPozycja.y + fWymiary1x1 + nMinOdl);
        ++nWiersz;
        nKolumna = 0;
    }
    else
    {
        pPozycja.x += wymiary.x * fWymiary1x1 + nMinOdl + (wymiary.x-1)*nMinOdl;
        nKolumna += wymiary.x;
    }
    ++nAktualny;
    ostSize = wymiary.x;
}

void UI::AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col, std::string str2)
{
    bool bk;
    do
    {
        bk = false;
        for (int i = nKolumna; i < wymiary.x+nKolumna && i < 4; ++i)
            for(int j = nWiersz; j < wymiary.y+nWiersz && j < 25; ++j)
                if (aEkran[i][j] == true)
                {
                    bk = true;
                    if (nKolumna < 4)
                    {
                        ++nKolumna;
                        pPozycja.x += fWymiary1x1 + nMinOdl;
                    }
                    else
                    {
                        nKolumna = 0;
                        pPozycja.x = nMinOdlLeftRight;
                        ++nWiersz;
                        pPozycja.y += nMinOdl + fWymiary1x1;
                    }
                }
    }while(bk);

    if ((pPozycja.x + nMinOdl + fWymiary1x1 + nMinOdlLeftRight) > pWymiary.x  && ostSize > 1)
    {
        pPozycja = pt::PointMake<float>(nMinOdlLeftRight, pPozycja.y + fWymiary1x1 + nMinOdl);
        ++nWiersz;
        nKolumna = 0;
    }
    sf::Image icon;
    icon.LoadFromFile(str2);
    objects[nAktualny] = new UIObject(wymiary.x * fWymiary1x1 + (wymiary.x-1)*nMinOdl, wymiary.y * fWymiary1x1 + (wymiary.y-1)*nMinOdl, pPozycja, str, col, icon);
    for (int i = nKolumna; i < wymiary.x+nKolumna && i < 4; ++i)
        for(int j = nWiersz; j < wymiary.y+nWiersz && j < 25; ++j)
            aEkran[i][j] = true;

    if ((pPozycja.x + nMinOdl + fWymiary1x1 + nMinOdlLeftRight) > pWymiary.x)
    {
        pPozycja = pt::PointMake<float>(nMinOdlLeftRight, pPozycja.y + fWymiary1x1 + nMinOdl);
        ++nWiersz;
        nKolumna = 0;
    }
    else
    {
        pPozycja.x += wymiary.x * fWymiary1x1 + nMinOdl + (wymiary.x-1)*nMinOdl;
        nKolumna += wymiary.x;
    }
    ++nAktualny;
    ostSize = wymiary.x;
}

void UI::AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col, int nKtory)
{

}

void UI::AddUIObject(std::string str, pt::Point<float> wymiary, sf::Color col, sf::Image& icon, int nKtory)
{

}

int UI::ShowUI(sf::RenderWindow& window)
{
    const sf::Input& wejscie = window.GetInput();
    sf::Event event;
    while (window.IsOpened())
    {
        while (window.GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
            {
                window.Close();
                return -1;
            }
            if (wejscie.IsKeyDown(sf::Key::Escape))
            {
                //window.Close();
                return -2;
            }
        }
        if (backimg)
            window.Draw(*backimg);
        for (int i = 0; i < ilosc; ++i)
            if (objects[i])
                if (objects[i]->ShowObject(window, wejscie))
                    return i;
        window.Display();
        if (backcol)
            window.Clear(*backcol);
        else
            window.Clear();
    }
}
