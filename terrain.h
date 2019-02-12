#ifndef TERRAIN_H
#define TERRAIN_H

#include <Box2D/Box2D.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "car.h"
#include "point.h"

class Terrain
{
	private:

        static const int kMaxHillKeyPoints = 1000;
        static const int kMaxHillVertices = 4000;
        static const int kMaxBorderVertices = 800;
        const int kHillSegmentWidth;

        pt::Point<float> pRozmiary;
        sf::Image coin5;
        sf::Image coin10;
        sf::Image coin50;
        sf::Image coin100;
        sf::Image coin500;
        sf::Image coin1000;
        sf::Image bak;
        sf::Image* buf;

        int hSegments;
        int hSegment;
        float dx;
        float da;
        float ymid;
        float ampl;

        pt::Point<float> p0;
        pt::Point<float> p1;
        pt::Point<float> pt0;
        pt::Point<float> pt1;

        int segment;

        int _offsetX;
        pt::Point<float> _hillKeyPoints[kMaxHillKeyPoints];

        int _fromKeyPointI;
        int _toKeyPointI;

        int _nHillVertices;
        pt::Point<float> _hillVertices[kMaxHillVertices];
        int _nBorderVertices;
        pt::Point<float> _borderVertices[kMaxBorderVertices];
        b2Body* _body;

        b2Vec2 lp[2];

        bool bPoczatek;
        int nZmiana;
        bool bBak;
        int ostBak;

        int LiczbaMonet;
        int ostCoin;

    public:

        sf::Sprite sBak;

        bool* moneta;
        sf::Sprite* coins;

        sf::Shape* sh;

        Terrain(b2World* world, Car& car, int SegmentWidth = 30, int nRand = 0);
        ~Terrain();

        void generateHills();
        void generateHills2();
        void generateHills3();
        void resetBox2DBody(b2World* _world, Car& car);
        void resetHillVertices(Car& car, DIRECTION dir);
        void RysujTrase(Car& car);
        void generateCoins(Car& car, int nLevel);
        void generateFuel();

        pt::Point<float> GetSize() const;
        float GetSegment() const;

        int GetCoinsNumber() const {return LiczbaMonet;};
        int GetLastCoin() const {return ostCoin;};
        float GetChangePos() const {return nZmiana;};
        bool Tank() const {return bBak;};
        float GetLastTank() const {return ostBak;};
        void IncraseChangePos(double d) {nZmiana += d;};
        void DecraseChangePos(double d) {nZmiana -= d;};
        void DisactivateTank() {bBak = false;};

};

#endif
