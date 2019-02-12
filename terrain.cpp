// generowanie terenu stworzone w oparciu o tutorial:
// https://www.raywenderlich.com/2723-how-to-create-a-game-like-tiny-wings-with-cocos2d-2-x-part-1

#include "terrain.h"
#include <cmath>
#include <ctime>
#include <iostream>
#define SCALE 100
#define PI 3.14159265359

Terrain::Terrain(b2World* world, Car& car, int SegmentWidth, int nRand) : kHillSegmentWidth(SegmentWidth)
{
    hSegments = 0;
    hSegment = 0;
    dx = 0;
    da = 0;
    ymid = 0;
    ampl = 0;
    p0 = 0;
    p1 = 0;
    pt0 = 0;
    pt1 = 0;
    segment = 0;
    _offsetX = 0;
    _fromKeyPointI = 0;
    _toKeyPointI = 0;
    _nHillVertices = 0;
    _nBorderVertices = 0;

    pRozmiary.x = 640;
    pRozmiary.y = 480;
    bPoczatek = true;
    nZmiana = GetSize().x / 8;
    coins = new sf::Sprite[2];
    moneta = new bool[2];
    bak.LoadFromFile("Images/bak.png");
    coin5.LoadFromFile("Images/5coin.png");
    coin10.LoadFromFile("Images/10coin.png");
    coin50.LoadFromFile("Images/50coin.png");
    coin100.LoadFromFile("Images/100coin.png");
    coin500.LoadFromFile("Images/500coin.png");
    coin1000.LoadFromFile("Images/1000coin.png");
    sBak.SetImage(bak);
    sBak.SetScale(0.5, 0.5);
    sBak.SetCenter(0, 0);
    bBak = false;
    ostBak = 0;
    sh = new sf::Shape[2];
    if (nRand == 0)
        generateHills();
    else if (nRand == 1)
        generateHills2();
    else if (nRand == 2)
        generateHills3();
    resetHillVertices(car, RIGHT);
    resetBox2DBody(world, car);
    RysujTrase(car);
    generateCoins(car, 0);

    bPoczatek = false;
    lp[0] = lp[1] = b2Vec2(0, 0);
    buf = 0;
}

Terrain::~Terrain()
{
    if (coins)
        delete[] coins;
    if (moneta)
        delete[] moneta;
    if (sh)
        delete[] sh;
}

void Terrain::generateHills()
{
    srand(time(NULL));
    int minDX = 300;
    int minDY = 80;
    int rangeDX = 800;
    int rangeDY = 10;

    float x = -minDX;
    float y = GetSize().y / 2 - minDY;
    float dy, ny, nx;
    short int sign = 1; // +1 - going up, -1 - going  down
    float paddingTop = 20;
    float paddingBottom = 20;

    for (int i = 0; i<kMaxHillKeyPoints; i++)
    {
        if (rangeDX > 100)
            --rangeDX;
        //if (rangeDY < 1800)
            rangeDY += 5;
        if (i == 0)
        {
            x = 0;
            y = GetSize().y / 2;
        }
        else
        {
            nx = rand() % rangeDX + minDX;
            x += nx;
            while(true)
            {
                dy = rand() % rangeDY + minDY;
                ny = y + dy * sign;
                if(ny < GetSize().y - paddingTop && ny > paddingBottom && dy/nx < 3)
                {
                    break;
                }
            }
            y = ny;
        }
        sign *= -1;
        _hillKeyPoints[i].x = x;
        _hillKeyPoints[i].y = y;
    }
}

void Terrain::generateHills2()
{
    srand(time(NULL));
    int minDX = 300;
    int minDY = 80;
    int rangeDX = 800;
    int rangeDY = 10;

    float x = -minDX;
    float y = GetSize().y / 2 - minDY;
    float dy, ny, nx;
    float paddingTop = 20;
    float paddingBottom = 20;

    for (int i = 0; i<kMaxHillKeyPoints; i++)
    {
        if (rangeDX > 100)
            --rangeDX;
        //if (rangeDY < 1800)
            rangeDY += 5;
        if (i == 0)
        {
            x = 0;
            y = GetSize().y / 2;
        }
        else
        {
            nx = rand() % rangeDX + minDX;
            x += nx;
            while(true)
            {
                dy = rand() % (rangeDY*2) + 1;
                dy -=rangeDY;
                if (dy < 0)
                    dy -= minDY;
                else
                    dy += minDY;
                ny = y + dy;
                if(ny < GetSize().y - paddingTop && ny > paddingBottom && dy/nx < 3)
                {
                    break;
                }
            }
            y = ny;
        }
        _hillKeyPoints[i].x = x;
        _hillKeyPoints[i].y = y;
    }
}

void Terrain::generateHills3()
{
    srand(time(NULL));
    int minDX = 100;
    int minDY = 10;
    int rangeDX = 1000;
    int rangeDY = 1000;

    float x = -minDX;
    float y = GetSize().y / 2 - minDY;
    float dy, ny, nx;
    float paddingTop = 20;
    float paddingBottom = 20;

    for (int i = 0; i<kMaxHillKeyPoints; i++)
    {
        if (rangeDX > 10 && rangeDY > 10)
        {
            rangeDX -= 4;
            rangeDY -= 2;
        }
        if (i == 0)
        {
            x = 0;
            y = GetSize().y / 2;
        }
        else
        {
            nx = rand() % rangeDX + minDX;
            x += nx;
            do
            {
                dy = rand() % (rangeDY*2) + 1;
                dy -=rangeDY;
                if (dy < 0)
                    dy -= minDY;
                else
                    dy += minDY;
                ny = y + dy;
            }while(ny > GetSize().y - paddingTop && ny < paddingBottom || (dy/nx > 0.5 || (dy < 0 && dy/nx < -0.5)));
            //if (i < 200)std::cout << dy << ' ' << nx << ' ' << dy/nx << std::endl;
            if(dy < 0 && dy/nx < -0.5) std::cout << dy/nx << std::endl;
            y = ny;
        }
        _hillKeyPoints[i].x = x;
        _hillKeyPoints[i].y = y;
    }
}

void Terrain::resetBox2DBody(b2World* _world, Car& car)
{
    if (bPoczatek)
    {
        b2BodyDef bd;
        _body = _world->CreateBody(&bd);

        b2EdgeShape shape;

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 0.0f;
        fd.friction = 0.6f;

        b2Vec2 p[2];

        p[0] = b2Vec2(_borderVertices[0].x / SCALE, _borderVertices[0].y / SCALE);
        p[1] = b2Vec2(_borderVertices[0].x / SCALE, 0);
        shape.Set(p[0], p[1]);
        _body->CreateFixture(&fd);
        lp[0] = p[0];
        lp[1] = p[1];

        for (int i = 0; i < _nBorderVertices - 2; i++)
        {
            p[0] = b2Vec2(_borderVertices[i].x / SCALE, _borderVertices[i].y / SCALE);
            p[1] = b2Vec2(_borderVertices[i+1].x / SCALE, _borderVertices[i+1].y / SCALE);
            shape.Set(p[0], p[1]);
            _body->CreateFixture(&fd);
        }
    }
    if(_body)
    {
        for (b2Fixture* f = _body->GetFixtureList(); f; )
        {
            b2Fixture* fixtureToDestroy = f;
            f = f->GetNext();
            _body->DestroyFixture(fixtureToDestroy);
            fixtureToDestroy = NULL;
        }

        b2EdgeShape shape;

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 0.0f;
        fd.friction = 0.6f;

        b2Vec2 p[2];
        if (car.GetDirection() == RIGHT && car.GetPosition().x - 25 > lp[0].x)
        {
            p[0] = b2Vec2(_borderVertices[0].x / SCALE, _borderVertices[0].y / SCALE);
            p[1] = b2Vec2(_borderVertices[0].x / SCALE, 0);
            while (p[0].x > car.GetPosition().x - 25 && !bPoczatek && p[0].x > 0)
            {
                --p[0].x;
                --p[1].x;
            }

            lp[0] = p[0];
            lp[1] = p[1];
        }
        else
        {
            p[0] = lp[0];
            p[1] = lp[1];
        }
        shape.Set(p[0], p[1]);
        _body->CreateFixture(&fd);

        for (int i = 0; i < _nBorderVertices - 1; i++)
        {
            //std::cout << _borderVertices[i].x / SCALE << ' ' << _borderVertices[i].y << std::endl;
            p[0] = b2Vec2(_borderVertices[i].x / SCALE, _borderVertices[i].y / SCALE);
            p[1] = b2Vec2(_borderVertices[i+1].x / SCALE, _borderVertices[i+1].y / SCALE);
            //std::cout << p[0].x << ' ' << p[0].y << ' ' << p[1].x << ' ' << p[1].y << std::endl;
            shape.Set(p[0], p[1]);
            _body->CreateFixture(&fd);
        }
    }
}

void Terrain::RysujTrase(Car& car)
{
    if (sh && !bPoczatek)
        delete[] sh;
    segment = 0;
    for(int i = _fromKeyPointI; i <= _toKeyPointI; ++i)
    {
        p0 = _hillKeyPoints[i-1];
        p1 = _hillKeyPoints[i];
        hSegment = floorf((p1.x-p0.x)/kHillSegmentWidth);
        segment += hSegment + 1;
    }
    sh = new sf::Shape[segment];
    int x = 0;
    for(int i = _fromKeyPointI; i <= _toKeyPointI; ++i)
    {
        p0 = _hillKeyPoints[i-1];
        p1 = _hillKeyPoints[i];
        hSegment = floorf((p1.x-p0.x)/kHillSegmentWidth);
        dx = (p1.x - p0.x) / hSegment;
        da = M_PI / hSegment;
        ymid = (p0.y + p1.y) / 2;
        ampl = (p0.y - p1.y) / 2;
        pt0 = p0;
        pt0.y += 300;
        for (int j = 0; j < hSegment+1; ++j)
        {
            pt1.x = p0.x + j*dx;
            pt1.y = 300 + ymid + ampl * cosf(da*j);
            sh[j+x].AddPoint(pt0.x, pt0.y, sf::Color::Black, sf::Color::Black);
            sh[j+x].AddPoint(pt1.x, pt1.y, sf::Color::Black, sf::Color::Black);
            sh[j+x].AddPoint(pt1.x, pt1.y + 640, sf::Color::Black, sf::Color::Black);
            sh[j+x].AddPoint(pt0.x, pt0.y + 640, sf::Color::Black, sf::Color::Black);
            pt0 = pt1;
        }
        x += hSegment+1;
    }
}

void Terrain::generateCoins(Car& car, int nLevel)
{
    if (coins)
        delete[] coins;
    if (moneta)
        delete[] moneta;
    LiczbaMonet = segment/2;
    coins = new sf::Sprite[LiczbaMonet];
    moneta = new bool[LiczbaMonet];
    for (int i = 0; i < LiczbaMonet; ++i)
        moneta[i] = true;
    int y = 0;
    if (nLevel < 2)
        buf = new sf::Image(coin5);
    else if (nLevel < 5)
        buf = new sf::Image(coin10);
    else if (nLevel < 7)
        buf = new sf::Image(coin50);
    else if (nLevel < 9)
        buf = new sf::Image(coin100);
    else if (nLevel < 16)
        buf = new sf::Image(coin500);
    else
        buf = new sf::Image(coin1000);
    for (int i = 1; i < segment - 1; ++i)
    {
        if (i % 2 == 0 && sh[i].GetPointPosition(1).x > car.car.GetPosition().x + 800)
        {
            coins[y].SetImage(*buf);
            coins[y].SetScale(0.23, 0.23);
            if (sh[i].GetPointPosition(1).y > sh[i+1].GetPointPosition(1).y)
            {
                coins[y].SetPosition(sh[i].GetPointPosition(1).x - 40, sh[i].GetPointPosition(1).y -60);
            }
            else if (sh[i].GetPointPosition(1).y < sh[i+1].GetPointPosition(1).y)
            {
                coins[y].SetPosition(sh[i].GetPointPosition(1).x + 40, sh[i].GetPointPosition(1).y - 60);
            }
            else
            {
                coins[y].SetPosition(sh[i].GetPointPosition(1).x, sh[i].GetPointPosition(1).y - 60);
            }
            ++y;
        }
    }
    ostCoin = coins[y-1].GetPosition().x;
}

void Terrain::generateFuel()
{
    if (sh[segment-2].GetPointPosition(1).y > sh[segment-1].GetPointPosition(1).y)
        sBak.SetPosition(sh[segment-2].GetPointPosition(1).x + 50, sh[segment-2].GetPointPosition(1).y - 70);
    else if (sh[segment-2].GetPointPosition(1).y < sh[segment-1].GetPointPosition(1).y)
        sBak.SetPosition(sh[segment-2].GetPointPosition(1).x - 50, sh[segment-2].GetPointPosition(1).y - 70);
    else
        sBak.SetPosition(sh[segment-2].GetPointPosition(1).x, sh[segment-2].GetPointPosition(1).y - 70);
    bBak = true;
    ostBak = sBak.GetPosition().x;
}

void Terrain::resetHillVertices(Car& car, DIRECTION dir)
{
    static int prevFromKeyPointI = -1;
    static int prevToKeyPointI = -1;
    _offsetX = car.car.GetPosition().x;
    // key points interval for drawing
    if (dir == RIGHT)
    {
        while (_hillKeyPoints[_fromKeyPointI+1].x < _offsetX - GetSize().x / 8)
        {
            _fromKeyPointI++;
        }
        while (_hillKeyPoints[_toKeyPointI].x < _offsetX + GetSize().x * 11 / 8)
        {
            _toKeyPointI++;
        }
    }
    else if (dir == LEFT)
    {
        while (_hillKeyPoints[_fromKeyPointI+1].x > _offsetX - GetSize().x * 11/8 && _fromKeyPointI > 0)
        {
            _fromKeyPointI--;
        }
        while (_hillKeyPoints[_toKeyPointI].x > _offsetX + GetSize().x * 15/8 && _toKeyPointI > 0)
        {
            _toKeyPointI--;
        }
    }
    if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI)
    {

        // vertices for visible area
        _nHillVertices = 0;
        _nBorderVertices = 0;
        p0 = _hillKeyPoints[_fromKeyPointI];
        for (int i = _fromKeyPointI+1; i<_toKeyPointI+1 && i < kMaxHillKeyPoints; i++)
        {
            p1 = _hillKeyPoints[i];

            // triangle strip between p0 and p1
            hSegments = ((p1.x-p0.x)/kHillSegmentWidth);
            dx = (p1.x - p0.x) / hSegments;
            da = M_PI / hSegments;
            ymid = (p0.y + p1.y) / 2;
            ampl = (p0.y - p1.y) / 2;
            pt0 = p0;
            _borderVertices[_nBorderVertices++] = pt0;
            for (int j=1; j<hSegments+1; j++)
            {
                pt1.x = p0.x + j*dx;
                pt1.y = ymid + ampl * cosf(da*j);
                _borderVertices[_nBorderVertices++] = pt1;

                _hillVertices[_nHillVertices++] = pt::PointMake<float>(pt0.x, 0);
                _hillVertices[_nHillVertices++] = pt::PointMake<float>(pt1.x, 0);

                _hillVertices[_nHillVertices++] = pt::PointMake(pt0.x, pt0.y);
                _hillVertices[_nHillVertices++] = pt::PointMake(pt1.x, pt1.y);

                pt0 = pt1;
            }

            p0 = p1;
        }

        prevFromKeyPointI = _fromKeyPointI;
        prevToKeyPointI = _toKeyPointI;

    }

}

pt::Point<float> Terrain::GetSize() const
{
    return pRozmiary;
}

float Terrain::GetSegment() const
{
    return segment;
}
