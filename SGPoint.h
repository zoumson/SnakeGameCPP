#pragma once

struct Point
{
    int y;
    int x;
    Point(int _y, int _x) : y(_y), x(_x) {};
    Point() : Point(0, 0) {};

    Point(const Point& t)       //copy constructor (member wise initialization)
    {
        y = t.y;
        x = t.x;
    };
    

    Point& operator=(const Point& t)       //copy constructor (member wise initialization)
    {
        y = t.y;
        x = t.x;
        return *this;
    };

    Point(Point&& t)
    {
        y = t.y;
        x = t.x;        
              
        t.y = 0;
        t.x = 0;
    }

    Point& operator=(Point&& t)
    {
        y = t.y;
        x = t.x;        
              
        t.y = 0;
        t.x = 0;

        return *this;
    }
};


inline bool operator==(const Point& left, const Point& right)
{
    return left.y == right.y &&
        left.x == right.x;
}