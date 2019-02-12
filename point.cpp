#include "point.h"

namespace pt
{
    Point PointMake(float x, float y)
    {
        Point p(x, y);
        return p;
    }

    Point::Point(float x1, float y1)
    {
        x = x1;
        y = y1;
    }

    Point::Point()
    {
        x = 0;
        y = 0;
    }
}
