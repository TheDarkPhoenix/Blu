#include "game.h"
#include "UI.h"
#include <cstdio>
#include <iostream>
#define SCALE 100

Game::Game()
{
    RamkaPaliwa = sf::Shape::Rectangle(40, 40, 160, 70, sf::Color::Black, 1.0f, sf::Color::Black);
    RamkaPaliwa.EnableFill(false);
    Paliwo = sf::Shape::Rectangle(40, 40, 160, 70, sf::Color::Black, 0.5f, sf::Color::Black);
    nLiczbaPunktow = 0;
    nLiczbaMetrow = 0;
    sprintf(c, "%i", nLiczbaPunktow);
    str1.SetText(c);
    sprintf(c, "%i", nLiczbaMetrow);
    str2.SetText(c);
    str1.SetColor(sf::Color::Black);
    str2.SetColor(sf::Color::Black);
    str1.SetScale(1.2f, 1.2f);
    str2.SetScale(1.2f, 1.2f);
    bak.LoadFromFile("Images/bak.png");
    bakG.SetImage(bak);
    bakG.SetScale(0.5, 0.5);
    punkty.LoadFromFile("Images/$.png");
    sPunkty.SetImage(punkty);
    sPunkty.SetScale(0.5, 0.5);
    Distance.LoadFromFile("Images/distance.png");
    sDistance.SetImage(Distance);
    sDistance.Scale(0.1, 0.1);
    bcg.LoadFromFile("Images/bc2.png");
    sBcg.SetImage(bcg);
    nCar = 0;
    nTrack = 0;
    muzyka.OpenFromFile("Music/Export16_3.wav");
    buf1.LoadFromFile("Sounds/acceleration.wav");
    buf2.LoadFromFile("Sounds/drive.wav");
    buf3.LoadFromFile("Sounds/slowing.wav");
    buf4.LoadFromFile("Sounds/engine.wav");
    ac.SetBuffer(buf1);
    dr.SetBuffer(buf2);
    sl.SetBuffer(buf3);
    en.SetBuffer(buf4);
    sounds[0] = false;
    sounds[1] = false;
    sounds[2] = false;
    nMusicVolume = 30;
    nSoundVolume = 100;
    trasa1 = 0;
    car1 = 0;
    nLevel = 1.5;
    nWartosc = 5;
    jb = false;
    nb = false;
}

bool Game::CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2)
{

    float Radius1 = (Object1.GetSize().x + Object1.GetSize().y) / 4;
    float Radius2 = (Object2.GetSize().x + Object2.GetSize().y) / 4;
    float xd = Object1.GetPosition().x - Object2.GetPosition().x;
    float yd = Object1.GetPosition().y - Object2.GetPosition().y;

    return sqrt(xd * xd + yd * yd) <= Radius1 + Radius2;
}

int Game::gra(sf::RenderWindow& window, int track)
{
    sf::Event event;
    const sf::Input& wejscie = window.GetInput();
    sf::View& kamera = window.GetDefaultView();

    sf::Clock zgr;
    sf::Clock clck;

    kamera.Zoom(0.75f);
    kamera.Move(620.0f, 0.0f);

    pt::Point<float> cam(620.0f, 0.0f);

    str1.SetPosition(kamera.GetRect().Left + 65, kamera.GetRect().Top + 2);
    str2.SetPosition(kamera.GetRect().Left + 60, kamera.GetRect().Top + 105);
    bakG.SetPosition(kamera.GetRect().Left + 3, kamera.GetRect().Top + 55);
    sPunkty.SetPosition(kamera.GetRect().Left + 10, kamera.GetRect().Top + 2);
    sDistance.SetPosition(kamera.GetRect().Left + 12, kamera.GetRect().Top + 110);
    RamkaPaliwa.SetPosition(kamera.GetRect().Left + 20, kamera.GetRect().Top + 25);
    Paliwo.SetPosition(kamera.GetRect().Left + 20, kamera.GetRect().Top + 25);
    sBcg.SetPosition(kamera.GetRect().Left, kamera.GetRect().Top);

    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);
    car1 = new Car(&world);
    int t = 30;
    if (track == 1 || track == 3 || track == 5)
        t = 150;
    int r = 0;
    if (track == 2 || track == 3)
        r = 1;
    else if (track == 4 || track == 5)
        r = 2;
    trasa1 = new Terrain(&world, *car1, t, r);
    if (muzyka.GetStatus() != sf::Sound::Playing)
        muzyka.Play();
    nLiczbaPunktow = 0;
    nLevel = 1.5;
    double dt;
    while (window.IsOpened())
    {
        dt = window.GetFrameTime();
        while (window.GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
            {
                muzyka.Stop();
                window.Close();
                return -1;
            }
            if (wejscie.IsKeyDown(sf::Key::Escape) || wejscie.IsKeyDown(sf::Key::P))
            {
                kamera.Zoom(1.333333333);
                kamera.Move(-cam.x, -cam.y);
                sBcg.Move(-cam.x, -cam.y);
                muzyka.Pause();
                StopSounds();
                int j = 0;
                do
                {
                    j = Game::Pause(window);
                    switch(j)
                    {
                        case -2:
                            if (car1)
                                delete car1;
                            if (trasa1)
                                delete trasa1;
                            muzyka.Stop();
                            return 0;
                            break;
                        case -1:
                            if (car1)
                                delete car1;
                            if (trasa1)
                                delete trasa1;
                            muzyka.Stop();
                            return -1;
                            break;
                        case 0:
                            if (car1)
                                delete car1;
                            if (trasa1)
                                delete trasa1;
                            muzyka.Stop();
                            return 1;
                            break;
                        case 1:
                            kamera.Zoom(0.75);
                            kamera.Move(cam.x, cam.y);
                            sBcg.Move(cam.x, cam.y);
                            muzyka.Play();
                            break;
                        case 2:
                            if (car1)
                                delete car1;
                        if (trasa1)
                            delete trasa1;
                            muzyka.Stop();
                            return 0;
                            break;
                        case 3:
                            {
                                bool b = Game::Settings(window);
                                if (!b)
                                {
                                    if (car1)
                                        delete car1;
                                    if (trasa1)
                                        delete trasa1;
                                    return -1;
                                }
                            }
                            break;
                    }
                }while(j == 3);
            }
        }
        if (wejscie.IsKeyDown(sf::Key::Left))
        {
            car1->SetB(0);
        }
        if (wejscie.IsKeyDown(sf::Key::Down))
        {
            car1->SetB(1);
        }
        if (wejscie.IsKeyDown(sf::Key::Right))
        {
            car1->SetB(2);
        }

        PlaySound(zgr);

        if (!car1->update(clck))
        {
            kamera.Zoom(1.333333333);
            kamera.Move(-cam.x, -cam.y);
            sBcg.Move(-cam.x, -cam.y);
            muzyka.Stop();
            StopSounds();
            int j = GameOver(window);
            if (car1)
                delete car1;
            if (trasa1)
                delete trasa1;
            switch (j)
            {
                case -2:
                    return 0;
                    break;
                case -1:
                    return -1;
                    break;
                case 0:
                    return 1;
                    break;
                case 1:
                    return 0;
                    break;
            }
        }
        if (car1->GetFuel() < 200)
            Paliwo = sf::Shape::Rectangle(RamkaPaliwa.GetPosition().x + 40, RamkaPaliwa.GetPosition().y + 40, RamkaPaliwa.GetPosition().x + 40 + car1->GetFuel() * 0.12f, RamkaPaliwa.GetPosition().y + 70, sf::Color::Red, 1.0f, sf::Color::Red);
        else
            Paliwo = sf::Shape::Rectangle(RamkaPaliwa.GetPosition().x + 40, RamkaPaliwa.GetPosition().y + 40, RamkaPaliwa.GetPosition().x + 40 + car1->GetFuel() * 0.12f, RamkaPaliwa.GetPosition().y + 70, sf::Color::Black, 1.0f, sf::Color::Black);
        nLiczbaMetrow = car1->GetPosition().x*2;
        if (car1->GetCarPosition().x > kamera.GetRect().Left || car1->GetCarPosition().x < kamera.GetRect().Right)
        {
            kamera.Move(car1->GetDistance().x * SCALE, 0);
            RamkaPaliwa.Move(car1->GetDistance().x * SCALE, 0);
            Paliwo.Move(car1->GetDistance().x * SCALE, 0);
            bakG.Move(car1->GetDistance().x * SCALE, 0);
            sPunkty.Move(car1->GetDistance().x * SCALE, 0);
            str1.Move(car1->GetDistance().x * SCALE, 0);
            str2.Move(car1->GetDistance().x * SCALE, 0);
            sDistance.Move(car1->GetDistance().x * SCALE, 0);
            sBcg.Move(car1->GetDistance().x * SCALE, 0);
            cam.x += car1->GetDistance().x * SCALE;
        }
        if (car1->GetCarPosition().y > kamera.GetRect().Top || car1->GetCarPosition().y < kamera.GetRect().Bottom)
        {
            kamera.Move(0, car1->GetDistance().y * SCALE);
            RamkaPaliwa.Move(0, car1->GetDistance().y * SCALE);
            Paliwo.Move(0, car1->GetDistance().y * SCALE);
            bakG.Move(0, car1->GetDistance().y * SCALE);
            sPunkty.Move(0, car1->GetDistance().y * SCALE);
            str1.Move(0, car1->GetDistance().y * SCALE);
            str2.Move(0, car1->GetDistance().y * SCALE);
            sDistance.Move(0, car1->GetDistance().y * SCALE);
            sBcg.Move(0, car1->GetDistance().y * SCALE);
            cam.y += car1->GetDistance().y * SCALE;
        }
        window.Draw(sBcg);
        if (car1->GetCarPosition().x + 20 > trasa1->GetChangePos())
        {
            trasa1->resetHillVertices(*car1, car1->GetDirection());
            trasa1->resetBox2DBody(&world, *car1);
            trasa1->RysujTrase(*car1);
            trasa1->IncraseChangePos(trasa1->GetSize().x/8);
        }
        else if (car1->GetCarPosition().x < trasa1->GetChangePos() - 100 && car1->GetDirection() == LEFT)
        {
            trasa1->resetHillVertices(*car1, car1->GetDirection());
            trasa1->resetBox2DBody(&world, *car1);
            trasa1->RysujTrase(*car1);
            trasa1->DecraseChangePos(trasa1->GetSize().x/8);
        }
        if (car1->GetCarPosition().x > trasa1->GetLastCoin() + 120)
        {
            if (nLevel < 2)
                nWartosc = 5;
            else if (nLevel < 5)
                nWartosc = 10;
            else if (nLevel < 7)
                nWartosc = 50;
            else if (nLevel < 9)
                nWartosc = 100;
            else if (nLevel < 16)
                nWartosc = 500;
            else
                nWartosc = 1000;
            trasa1->generateCoins(*car1, nLevel);
        }
        if ((!trasa1->Tank() && car1->GetCarPosition().x > trasa1->GetLastTank() + (1000*nLevel)) || nb)
        {
            trasa1->generateFuel();
            jb = true;
            nb = false;
            if (car1->GetCarPosition().x / 7500 > 1.5)
                nLevel = car1->GetCarPosition().x / 7500;
        }
        for (int j = 0; j < trasa1->GetSegment(); ++j)
            window.Draw(trasa1->sh[j]);

        for (int k = 0; k < trasa1->GetCoinsNumber(); ++k)
        {
            if (trasa1->moneta[k])
            {
                if (CircleTest(car1->car, trasa1->coins[k]))
                {
                    trasa1->moneta[k] = false;
                    nLiczbaPunktow += nWartosc;
                }
                else
                    window.Draw(trasa1->coins[k]);
                if (jb)
                    if (CircleTest(trasa1->sBak, trasa1->coins[k]))
                        nb = true;
            }
        }
        if (trasa1->Tank())
        {
            window.Draw(trasa1->sBak);
            if (CircleTest(car1->car, trasa1->sBak))
            {
                trasa1->DisactivateTank();
                car1->SetFuel();
            }
            if (car1->GetCarPosition().x - trasa1->sBak.GetPosition().x > 400)
            {
                trasa1->DisactivateTank();
            }
        }
        sprintf(c, "%i", nLiczbaPunktow);
        str1.SetText(c);
        sprintf(c, "%i", nLiczbaMetrow);
        str2.SetText(c);
        window.Draw(Paliwo);
        window.Draw(RamkaPaliwa);
        window.Draw(sPunkty);
        window.Draw(bakG);
        window.Draw(sDistance);
        window.Draw(str1);
        window.Draw(str2);
        window.Draw(car1->car);
        window.Draw(car1->koloL);
        window.Draw(car1->koloP);
        window.Display();
        window.Clear(sf::Color::White);
        world.Step(dt, 6, 2);
        jb = false;
    }
    muzyka.Stop();
    if (car1)
        delete car1;
    if (trasa1)
        delete trasa1;
    return 0;
}

void Game::StopSounds()
{
    if (dr.GetStatus() == sf::Sound::Playing)
    {
        if (dr.GetLoop() == true)
            dr.SetLoop(false);
        dr.Stop();
    }
    if (ac.GetStatus() == sf::Sound::Playing)
    {
        ac.Stop();
    }
    if (en.GetStatus() == sf::Sound::Playing)
    {
        if (en.GetLoop() == true)
            en.SetLoop(false);
        en.Stop();
    }
    if (sl.GetStatus() == sf::Sound::Playing)
    {
        sl.Stop();
    }
}

void Game::PlaySound(sf::Clock& zgr)
{
    if (car1->GetB() == -1 && sl.GetStatus() != sf::Sound::Playing && !sounds[2])
    {
        if (dr.GetStatus() == sf::Sound::Playing)
        {
            if (dr.GetLoop() == true)
                dr.SetLoop(false);
            dr.Stop();
        }
        else if (ac.GetStatus() == sf::Sound::Playing)
        {
            ac.Stop();
        }
        else if (en.GetStatus() == sf::Sound::Playing)
        {
            if (en.GetLoop() == true)
                en.SetLoop(false);
            en.Stop();
        }
        if (zgr.GetElapsedTime() > 0.2 || sounds[1] == true)
            sl.Play();
        sounds[2] = true;
        sounds[0] = false;
        sounds[1] = false;
        zgr.Reset();
    }
    else if (car1->GetB() == 2 || car1->GetB() == 0)
    {
        if (ac.GetStatus() != sf::Sound::Playing && !sounds[0])
        {
            if (sl.GetStatus() == sf::Sound::Playing)
            {
                sl.Stop();
            }
            else if (dr.GetStatus() == sf::Sound::Playing)
            {
                if (dr.GetLoop() == true)
                    dr.SetLoop(false);
                dr.Stop();
            }
            else if (en.GetStatus() == sf::Sound::Playing)
            {
                if (en.GetLoop() == true)
                    en.SetLoop(false);
                en.Stop();
            }
            ac.Play();
            sounds[0] = true;
            sounds[1] = false;
            sounds[2] = false;
        }
        else
        {
            if (sl.GetStatus() == sf::Sound::Playing)
            {
                sl.Stop();
            }
            else if (en.GetStatus() == sf::Sound::Playing)
            {
                if (en.GetLoop() == true)
                    en.SetLoop(false);
                en.Stop();
            }
            else if (!(ac.GetStatus() == sf::Sound::Playing))
            {
                if (dr.GetLoop() == false)
                {
                    dr.SetLoop(true);
                    dr.Play();
                }
                sounds[1] = true;
                sounds[2] = false;
            }
            zgr.Reset();
        }
    }
    else
    {
        if (ac.GetStatus() == sf::Sound::Playing)
        {
            ac.Stop();
        }
        else if (dr.GetStatus() == sf::Sound::Playing)
        {
            if (dr.GetLoop() == true)
                dr.SetLoop(false);
            dr.Stop();
        }
        if (en.GetLoop() == false && !(sl.GetStatus() == sf::Sound::Playing))
        {
            en.SetLoop(true);
            en.Play();
        }
        zgr.Reset();
    }
}

bool Game::Settings(sf::RenderWindow& window)
{
    sf::Event event;
    const sf::Input& wejscie = window.GetInput();
    sf::String strMusic("Music Volume");
    strMusic.SetPosition(70, 40);
    strMusic.SetColor(sf::Color::Black);
    sf::Shape RMusic = sf::Shape::Rectangle(70, 80, 570, 120, sf::Color::Black, 2.0f, sf::Color::Black);
    RMusic.EnableFill(false);
    sf::Shape Music = sf::Shape::Rectangle(70, 80, nMusicVolume * 5 + 70, 120, sf::Color::Black, 2.0f, sf::Color::Black);
    sf::String strSound("Sound Volume");
    strSound.SetPosition(70, 140);
    strSound.SetColor(sf::Color::Black);
    sf::Shape RSound = sf::Shape::Rectangle(70, 180, 570, 220, sf::Color::Black, 2.0f, sf::Color::Black);
    RSound.EnableFill(false);
    sf::Shape Sound = sf::Shape::Rectangle(70, 180, nSoundVolume * 5 + 70, 220, sf::Color::Black, 2.0f, sf::Color::Black);

    sf::Image imgPlus;
    imgPlus.LoadFromFile("Images/plus.png");
    sf::Sprite sPlus1;
    sPlus1.SetImage(imgPlus);
    sf::Sprite sPlus2;
    sPlus2.SetImage(imgPlus);
    sPlus1.Scale(0.2, 0.2);
    sPlus2.Scale(0.2, 0.2);
    sPlus1.SetPosition(585, 90);
    sPlus2.SetPosition(585, 190);

    sf::Image imgMinus;
    imgMinus.LoadFromFile("Images/minus.png");
    sf::Sprite sMinus1;
    sMinus1.SetImage(imgMinus);
    sf::Sprite sMinus2;
    sMinus2.SetImage(imgMinus);
    sMinus1.Scale(0.2, 0.2);
    sMinus2.Scale(0.2, 0.2);
    sMinus1.SetPosition(25, 90);
    sMinus2.SetPosition(25, 190);

    pt::Point<float> MPos(0, 0);

    while(window.IsOpened())
    {
        while(window.GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
            {
                window.Close();
                return false;
            }
            if (wejscie.IsKeyDown(sf::Key::Escape))
            {
                muzyka.SetVolume(nMusicVolume);
                ac.SetVolume(nSoundVolume);
                dr.SetVolume(nSoundVolume);
                sl.SetVolume(nSoundVolume);
                en.SetVolume(nSoundVolume);
                return true;
            }
            if (wejscie.IsMouseButtonDown(sf::Mouse::Left))
                MPos = pt::PointMake<float>(wejscie.GetMouseX(), wejscie.GetMouseY());
            if (wejscie.IsKeyDown(sf::Key::B))
            {
                muzyka.SetVolume(nMusicVolume);
                ac.SetVolume(nSoundVolume);
                dr.SetVolume(nSoundVolume);
                sl.SetVolume(nSoundVolume);
                en.SetVolume(nSoundVolume);
                return true;
            }
        }
        if (MPos.x || MPos.y)
        {
            if (MPos.x > sPlus1.GetPosition().x && MPos.x < sPlus1.GetPosition().x + 20 && MPos.y > sPlus1.GetPosition().y && MPos.y < sPlus1.GetPosition().y + 20 && nMusicVolume < 100)
                ++nMusicVolume;
            else if (MPos.x > sMinus1.GetPosition().x && MPos.x < sMinus1.GetPosition().x + 20 && MPos.y > sMinus1.GetPosition().y && MPos.y < sMinus1.GetPosition().y + 20 && nMusicVolume > 0)
                --nMusicVolume;
            else if (MPos.x > sPlus2.GetPosition().x && MPos.x < sPlus2.GetPosition().x + 20 && MPos.y > sPlus2.GetPosition().y && MPos.y < sPlus2.GetPosition().y + 20 && nSoundVolume < 100)
                ++nSoundVolume;
            else if (MPos.x > sMinus2.GetPosition().x && MPos.x < sMinus2.GetPosition().x + 20 && MPos.y > sMinus2.GetPosition().y && MPos.y < sMinus2.GetPosition().y + 20 && nSoundVolume > 0)
                --nSoundVolume;
        }
        Music = sf::Shape::Rectangle(70, 80, nMusicVolume * 5 + 70, 120, sf::Color::Black, 2.0f, sf::Color::Black);
        Sound = sf::Shape::Rectangle(70, 180, nSoundVolume * 5 + 70, 220, sf::Color::Black, 2.0f, sf::Color::Black);
        window.Draw(sBcg);
        window.Draw(strMusic);
        window.Draw(RMusic);
        window.Draw(Music);
        window.Draw(strSound);
        window.Draw(RSound);
        window.Draw(Sound);
        window.Draw(sPlus1);
        window.Draw(sPlus2);
        window.Draw(sMinus1);
        window.Draw(sMinus2);
        window.Display();
        window.Clear(sf::Color::White);
        MPos = pt::PointMake<float>(0, 0);
    }
    muzyka.SetVolume(nMusicVolume);
    ac.SetVolume(nSoundVolume);
    dr.SetVolume(nSoundVolume);
    sl.SetVolume(nSoundVolume);
    en.SetVolume(nSoundVolume);
    return true;
}

int Game::Pause(sf::RenderWindow& window)
{
    UI pauseUI(pt::PointMake<float>(640, 480), bcg, 4);
    pauseUI.AddUIObject("Restart",  pt::PointMake<float>(1, 1), sf::Color::Black, "Images/restart.png");
    pauseUI.AddUIObject("Resume",  pt::PointMake<float>(1, 1), sf::Color::Black, "Images/resume.png");
    pauseUI.AddUIObject("Home",  pt::PointMake<float>(1, 1), sf::Color::Black, "Images/home.png");
    pauseUI.AddUIObject("Settings",  pt::PointMake<float>(1, 1), sf::Color::Black, "Images/settings.png");
    int i = pauseUI.ShowUI(window);
    return i;
}

int Game::GameOver(sf::RenderWindow& window)
{
    UI endUI(pt::PointMake<float>(640, 480), bcg, 2);
    endUI.AddUIObject("Restart", pt::PointMake<float>(2, 1), sf::Color::Black, "Images/restart.png");
    endUI.AddUIObject("Home", pt::PointMake<float>(2, 1), sf::Color::Black, "Images/home.png");
    return endUI.ShowUI(window);
}

bool Game::Menu(sf::RenderWindow& window)
{
    int i = 0;
    while (i != 5)
    {
        UI gameUI(pt::PointMake<float>(640, 480), bcg, 6);
        gameUI.AddUIObject("Start", pt::PointMake<float>(2, 1), sf::Color::Black, "Images/HillRacing2.png");
        gameUI.AddUIObject("Car", pt::PointMake<float>(2, 1), sf::Color::Black, "Images/car5.png");
        gameUI.AddUIObject("Track", pt::PointMake<float>(2, 1), sf::Color::Black, "Images/trasaobr1.png");
        gameUI.AddUIObject("Upgrades", pt::PointMake<float>(2, 1), sf::Color::Black, "Images/car5.png");
        gameUI.AddUIObject("Settings", pt::PointMake<float>(1, 1), sf::Color::Black, "Images/settings.png");
        gameUI.AddUIObject("Exit", pt::PointMake<float>(1, 1), sf::Color::Black, "Images/exit.png");
        i = gameUI.ShowUI(window);
        switch(i)
        {
            case -2:

                break;
            case -1:
                return false;
                break;
            case 0:
                {
                    int i = 0;
                    do
                    {
                        i = gra(window, nTrack);
                        if (i == -1)
                            return false;
                    }
                    while(i == 1);
                }
                break;
            case 1:
                {
                    UI carUI(pt::PointMake<float>(640, 480), bcg, 2);
                    carUI.AddUIObject("Car1", pt::PointMake<float>(2, 1), sf::Color::Black, "Images/car5.png");
                    carUI.AddUIObject("Back", pt::PointMake<float>(1, 1), sf::Color::Black);
                    nCar = carUI.ShowUI(window);
                    if (nCar == -1)
                        return false;
                    else if (nCar == -2)
                        nCar = 0;
                }
                break;
            case 2:
                {
                    UI trackUI(pt::PointMake<float>(640, 480), bcg, 7);
                    trackUI.AddUIObject("Track1", pt::PointMake<float>(1, 1), sf::Color::Black);
                    trackUI.AddUIObject("Track2", pt::PointMake<float>(1, 1), sf::Color::Black);
                    trackUI.AddUIObject("Track3", pt::PointMake<float>(1, 1), sf::Color::Black);
                    trackUI.AddUIObject("Track4", pt::PointMake<float>(1, 1), sf::Color::Black);
                    trackUI.AddUIObject("Track5", pt::PointMake<float>(1, 1), sf::Color::Black);
                    trackUI.AddUIObject("Track6", pt::PointMake<float>(1, 1), sf::Color::Black);
                    trackUI.AddUIObject("Back", pt::PointMake<float>(1, 1), sf::Color::Black);
                    nTrack = trackUI.ShowUI(window);
                    if (nTrack == -1)
                        return false;
                    else if (nTrack == -2)
                        nTrack = 0;
                }
                break;
            case 3:
                break;
            case 4:
                {
                    bool b1 = Settings(window);
                    std::cout << b1 << std::endl;
                    if (!b1)
                        return false;
                }
                break;
            case 5:
                break;
        }
    }
    return true;
}
