#include "UIObject.h"
#include <iostream>
#include <string>

UIObject::UIObject()
{
    pWymiary = 0.0f;
    pPozycja = 0.0f;
    str.SetText("Nothing");
    sh = sf::Shape::Rectangle(0, 0, 10, 10, sf::Color::Black, 1.0f, sf::Color::Black);
    bImage = false;
}

UIObject::UIObject(pt::Point<float> wymiary, pt::Point<float> pozycja, std::string str1, sf::Color cl)
{
    pWymiary = wymiary;
    pPozycja = pozycja;
    str.SetText(str1);
    str.SetCenter(str.GetRect().Right/2, 0);
    str.SetPosition(pozycja.x + wymiary.x/2, pozycja.y);
    sh = sf::Shape::Rectangle(pPozycja.x, pPozycja.y, pPozycja.x + pWymiary.x, pPozycja.y + pWymiary.y, cl, 1.0f, cl);
    bImage = false;
}

UIObject::UIObject(pt::Point<float> wymiary, pt::Point<float> pozycja, std::string str1, sf::Color cl, sf::Image img1)
{
    pWymiary = wymiary;
    pPozycja = pozycja;
    str.SetText(str1);
    str.SetCenter(str.GetRect().Right/2, 0);
    str.SetPosition(pozycja.x + pWymiary.x/2, pozycja.y);
    sh = sf::Shape::Rectangle(pPozycja.x, pPozycja.y, pPozycja.x + pWymiary.x, pPozycja.y + pWymiary.y, cl, 1.0f, cl);
    bImage = true;
    sImg = new sf::Sprite;
    img = new sf::Image(img1);
    sImg->SetImage(*img);

    if (sImg->GetSize().x > pWymiary.x - 20)
    {
        sImg->Resize(pWymiary.x - 20, (pWymiary.x-20)*(sImg->GetSize().y/sImg->GetSize().x));
    }
    if (sImg->GetSize().y > pWymiary.y - (str.GetRect().Bottom-pPozycja.y) - 10)
    {
        sImg->Resize((pWymiary.y - (str.GetRect().Bottom-pPozycja.y) -10)*(sImg->GetSize().x/sImg->GetSize().y), pWymiary.y - (str.GetRect().Bottom-pPozycja.y) -10);
    }
    sImg->SetCenter(img->GetWidth()/2, 0);
    sImg->SetPosition(pPozycja.x + pWymiary.x/2, str.GetRect().Bottom+5);
}

UIObject::UIObject(float wymiaryX, float wymiaryY, pt::Point<float> pozycja, std::string str1, sf::Color cl)
{
    pWymiary = pt::PointMake(wymiaryX, wymiaryY);
    pPozycja = pozycja;
    str.SetText(str1);
    str.SetCenter(str.GetRect().Right/2, 0);
    str.SetPosition(pozycja.x + pWymiary.x/2, pozycja.y);
    sh = sf::Shape::Rectangle(pPozycja.x, pPozycja.y, pPozycja.x + pWymiary.x, pPozycja.y + pWymiary.y, cl, 1.0f, cl);
    bImage = false;
}

UIObject::UIObject(float wymiaryX, float wymiaryY, pt::Point<float> pozycja, std::string str1, sf::Color cl, sf::Image img1)
{
    pWymiary = pt::PointMake(wymiaryX, wymiaryY);
    pPozycja = pozycja;
    str.SetText(str1);
    str.SetCenter(str.GetRect().Right/2, 0);
    str.SetPosition(pozycja.x + pWymiary.x/2, pozycja.y);
    sh = sf::Shape::Rectangle(pPozycja.x, pPozycja.y, pPozycja.x + pWymiary.x, pPozycja.y + pWymiary.y, cl, 1.0f, cl);
    bImage = true;
    sImg = new sf::Sprite;
    img = new sf::Image(img1);
    sImg->SetImage(*img);
    if (sImg->GetSize().x > pWymiary.x - 20)
    {
        sImg->Resize(pWymiary.x - 20, (pWymiary.x-20)*(sImg->GetSize().y/sImg->GetSize().x));
    }
    if (sImg->GetSize().y > pWymiary.y - (str.GetRect().Bottom-pPozycja.y) - 10)
    {
        sImg->Resize((pWymiary.y - (str.GetRect().Bottom-pPozycja.y) -10)*(sImg->GetSize().x/sImg->GetSize().y), pWymiary.y - (str.GetRect().Bottom-pPozycja.y) -10);
    }
    sImg->SetCenter(img->GetWidth()/2, 0);
    sImg->SetPosition(pPozycja.x + pWymiary.x/2, str.GetRect().Bottom+5);
}

bool UIObject::ShowObject(sf::RenderWindow& window, const sf::Input& wejscie)
{
    window.Draw(sh);
    window.Draw(str);
    if (bImage)
        window.Draw(*sImg);
    if (wejscie.IsMouseButtonDown(sf::Mouse::Left) && (wejscie.GetMouseX() > pPozycja.x && wejscie.GetMouseX() < pPozycja.x + pWymiary.x) && (wejscie.GetMouseY() > pPozycja.y && wejscie.GetMouseY() < pPozycja.y + pWymiary.y))
        return true;
    else
        return false;
}
