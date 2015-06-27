// Point.h: interface for the Point class.
//
//////////////////////////////////////////////////////////////////////

#ifndef POINT_H
#define POINT_H

namespace PDC
{

class Point
{
public:
    double x;
    double y;
    double z;
	Point();
    Point(double x,double y,double z);
	virtual ~Point();
};

}

#endif
