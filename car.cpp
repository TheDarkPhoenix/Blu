#include "car.h"
#include <iostream>
#define SCALE 100

Car::Car(b2World* m_world)
{
    m_hz = 11.0f;
    m_zeta = 2.7f;
    m_speed = 50.0f;

    b2Body* ground = NULL;

    // Car
    {
        b2PolygonShape chassis;
        b2Vec2 vertices[8];
        vertices[0].Set(-1.05f, -0.0375f);
        vertices[1].Set(-0.5f, -0.344f);
        vertices[2].Set(0.3f, -0.344f);
        vertices[3].Set(0.625f, -0.0375f);
        vertices[4].Set(0.9375f, 0.0f);
        vertices[5].Set(1.05f, 0.344f);
        vertices[6].Set(-1.05f, 0.344f);
        chassis.Set(vertices, 7);

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(6.4f, -0.5f);

        m_car = m_world->CreateBody(&bd);
        m_car->CreateFixture(&chassis, 1.0f);

        b2CircleShape circle;
        circle.m_radius = 0.20f;

        b2FixtureDef fd;
        fd.shape = &circle;
        fd.density = 1.0f;
        fd.friction = 2.7f;

        bd.position.Set(m_car->GetPosition().x - 0.65f , m_car->GetPosition().y + 0.45f);
        m_wheel1 = m_world->CreateBody(&bd);
        m_wheel1->CreateFixture(&fd);

        bd.position.Set(m_car->GetPosition().x + 0.60f, m_car->GetPosition().y + 0.4f);
        m_wheel2 = m_world->CreateBody(&bd);
        m_wheel2->CreateFixture(&fd);

        b2WheelJointDef jd;
        b2Vec2 axis(0.0f, 1.0f);

        jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 20.0f;
        jd.enableMotor = true;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

        jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 10.0f;
        jd.enableMotor = true;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);
    }
    CarChase.LoadFromFile("Images/chase3.png");
    car.SetImage(CarChase);
    car.Scale(0.2, 0.2);
    car.SetCenter(525, 172);
    CarWheelL.LoadFromFile("Images/kolo1.png");
    koloL.SetImage(CarWheelL);
    koloL.Scale(0.1, 0.1);
    koloL.SetCenter(250, 250);
    CarWheelR.LoadFromFile("Images/kolo1.png");
    koloP.SetImage(CarWheelR);
    koloP.Scale(0.1, 0.1);
    koloP.SetCenter(250, 250);
    b[0] = false;
    b[1] = false;
    b[2] = false;
    Pozycja.x = m_car->GetPosition().x;
    Pozycja.y = m_car->GetPosition().y;
    odleglosc.x = 0;
    odleglosc.y = 0;
    fPaliwo = fMaxPaliwo;
    pos[0] = 0;
    pos[1] = GetCarPosition().x;
    dir = RIGHT;
}
bool Car::update(sf::Clock& clck)
{
    m_spring1->EnableMotor(true);
    m_spring2->EnableMotor(true);
    if (b[2] && fPaliwo)
    {
        m_spring1->SetMotorSpeed(m_speed);
        m_spring2->SetMotorSpeed(m_speed);
        if (fPaliwo - 1.0 >= 0)
            fPaliwo -= 1.0;
        else
            fPaliwo = 0.0f;
    }
    else if (b[1])
    {
        m_spring1->SetMotorSpeed(0.0f);
        m_spring2->SetMotorSpeed(0.0f);
    }
    else if (b[0] && fPaliwo)
    {
        m_spring1->SetMotorSpeed(-m_speed);
        m_spring2->SetMotorSpeed(-m_speed);
        if (fPaliwo - 1.0 >= 0)
            fPaliwo -= 1.0;
        else
            fPaliwo = 0.0f;
    }
    else
    {
        m_spring1->EnableMotor(false);
        m_spring2->EnableMotor(false);
    }
    b[2] = false;
    b[0] = false;
    b[1] = false;
    car.SetPosition(m_car->GetPosition().x*SCALE, 300 + m_car->GetPosition().y*SCALE);
    car.SetRotation(-m_car->GetAngle()*57.29577951);
    if ((car.GetRotation() > 120 && car.GetRotation() < 240 && GetSpeed() < 1) || (!fPaliwo && GetSpeed() < 5))
    {
        //std::cout << clck.GetElapsedTime() << std::endl;
        if(clck.GetElapsedTime() > 6)
            clck.Reset();
        if(clck.GetElapsedTime() > 4 && (!fPaliwo && GetSpeed() < 5))
            return false;
        else if (clck.GetElapsedTime() > 2)
            return false;
        //m_car->SetTransform(m_car->GetPosition(), 0.0f);
    }
    koloL.SetPosition(m_wheel1->GetPosition().x*SCALE, 300 + m_wheel1->GetPosition().y*SCALE);
    koloL.SetRotation(-m_wheel1->GetAngle()*57.29577951);
    koloP.SetPosition(m_wheel2->GetPosition().x*SCALE, 300 + m_wheel2->GetPosition().y*SCALE);
    koloP.SetRotation(-m_wheel2->GetAngle()*57.29577951);
    odleglosc.x = m_car->GetPosition().x - Pozycja.x;
    odleglosc.y = m_car->GetPosition().y - Pozycja.y;
    Pozycja.x = m_car->GetPosition().x;
    Pozycja.y = m_car->GetPosition().y;
    pos[0] = pos[1];
    pos[1] = GetCarPosition().x;
    if (pos[0] > pos[1])
        dir = LEFT;
    else
        dir = RIGHT;
    return true;
}

void Car::SetB(int i)
{
    if (!(i < 0 || i > 2))
        b[i] = true;
}
