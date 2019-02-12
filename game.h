#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>

#include "car.h"
#include "terrain.h"

class Game
{
    private:

        int nSkala;
        int nLiczbaPunktow;
        int nLiczbaMetrow;
        sf::Shape RamkaPaliwa;
        sf::Shape Paliwo;

        sf::Image bak;
        sf::Image punkty;
        sf::Image Distance;
        sf::Image bcg;

        sf::Sprite bakG;
        sf::Sprite sPunkty;
        sf::Sprite sDistance;
        sf::Sprite sBcg;

        sf::String str1;
        sf::String str2;
        char c[50];

        int nCar;
        int nTrack;

        sf::Music muzyka;

        sf::SoundBuffer buf1;
        sf::SoundBuffer buf2;
        sf::SoundBuffer buf3;
        sf::SoundBuffer buf4;

        sf::Sound ac;
        sf::Sound dr;
        sf::Sound sl;
        sf::Sound en;

        bool sounds[3];

        int nSoundVolume;
        int nMusicVolume;

        Terrain* trasa1;
        Car* car1;

        float nLevel;
        int nWartosc;
        bool jb;
        bool nb;

    public:

        Game();
        //~Game();

        bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
        int gra(sf::RenderWindow& window, int track);
        bool Menu(sf::RenderWindow& window);
        bool Settings(sf::RenderWindow& window);
        int Pause(sf::RenderWindow& window);
        void PlaySound(sf::Clock& zgr);
        int GameOver(sf::RenderWindow& window);
        void StopSounds();
};

#endif
