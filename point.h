#ifndef POINT_H
#define POINT_H

namespace pt
{
    template <typename T>
    class Point
    {
        public:

            T x;
            T y;

            Point<T>(T x1, T y1){x = x1;y = y1;};
            Point<T>(){x = 0;y = 0;};

            /*Point operator =(Point<T> p)
            {
                if (&p != this)
                {
                    x = p.x;
                    y = p.y;
                }
                return *this;
            }*/

            Point operator =(T f)
            {
                x = f;
                y = f;
                return *this;
            };

            Point operator *(Point<T> p)
            {
                Point<T> p1 = *this;
                p1.x *= p.x;
                p1.y *= p.y;
                return p1;
            };

            Point operator *(T f)
            {
                Point<T> p = *this;
                p.x *= f;
                p.y *= f;
                return p;
            };

            Point operator /(Point<T> p)
            {
                Point<T> p1 = *this;
                p1.x /= p.x;
                p1.y /= p.y;
                return p1;
            };

            Point operator /(T f)
            {
                Point<T> p = *this;
                p.x /= f;
                p.y /= f;
                return p;
            };

            Point operator +(Point<T> p)
            {
                Point<T> p1 = *this;
                p1.x += p.x;
                p1.y += p.y;
                return p1;
            };

            Point operator +(T f)
            {
                Point<T> p = *this;
                p.x += f;
                p.y += f;
                return p;
            };

            Point operator -(Point<T> p)
            {
                Point<T> p1 = *this;
                p1.x -= p.x;
                p1.y -= p.y;
                return p1;
            };

            Point operator -(T f)
            {
                Point<T> p = *this;
                p.x -= f;
                p.y -= f;
                return p;
            };

            Point operator -()
            {
                Point<T> p;
                p.x = -x;
                p.y  = -y;
                return p;
            };

            Point operator +=(Point<T> p)
            {
                x += p.x;
                y += p.y;
                return *this;
            };

            Point operator +=(T f)
            {
                x += f;
                y += f;
                return *this;
            };

            Point operator -=(Point<T> p)
            {
                x -= p.x;
                y -= p.y;
                return *this;
            };

            Point operator -=(T f)
            {
                x -= f;
                y -= f;
                return *this;
            };

            Point operator *=(Point<T> p)
            {
                x *= p.x;
                y *= p.y;
                return *this;
            };

            Point operator *=(T f)
            {
                x *= f;
                y *= f;
                return *this;
            };

            Point operator /=(Point<T> p)
            {
                x /= p.x;
                y /= p.y;
                return *this;
            };

            Point operator /=(T f)
            {
                x /= f;
                y /= f;
                return *this;
            };

            Point operator %(Point<T> p)
            {
                Point<T> p1;
                p1.x /= x % p.x;
                p1.y /= y % p.y;
                return p1;
            };

            Point operator %(T f)
            {
                Point<T> p1;
                p1.x /= x % f;
                p1.y /= y % f;
                return p1;
            };
    };

    template<typename T>
    Point<T> PointMake(T x, T y)
    {
        Point<T> p(x, y);
        return p;
    }
}
#endif
