#ifndef CAR_H
#define CAR_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <string>
#include "point.h"

enum DIRECTION {RIGHT = 0, LEFT = 1};

class Car
{
    private:

        b2Body* m_wheel1;
        b2Body* m_wheel2;

        float m_hz;
        float m_zeta;
        float m_speed;
        b2WheelJoint* m_spring1;
        b2WheelJoint* m_spring2;

        sf::Image CarChase;
        sf::Image CarWheelR;
        sf::Image CarWheelL;

        bool b[3];
        pt::Point<float> odleglosc;
        pt::Point<float> Pozycja;
        float fPaliwo;
        static const float fMaxPaliwo = 1000;

        DIRECTION dir;
        float pos[2];

    public:
        b2Body* m_car;

        sf::Sprite car;
        sf::Sprite koloL;
        sf::Sprite koloP;

        Car(b2World* m_world);
        //~Car();

        bool update(sf::Clock& clck);
        void SetB(int i);

        int GetB() {for (int i = 0; i < 3; ++i) if (b[i]) return i; return -1;}

        pt::Point<float> GetPosition() const {return Pozycja;};
        pt::Point<float> GetDistance() const {return odleglosc;};
        pt::Point<float> GetCarPosition() const {return pt::PointMake(car.GetPosition().x, car.GetPosition().y);};
        DIRECTION GetDirection() const {return dir;};
        float GetFuel() const {return fPaliwo;};
        void SetFuel() {fPaliwo = fMaxPaliwo;};
        float GetSpeed() const {return m_car->GetLinearVelocity().Normalize() * 10;};
};

#endif
