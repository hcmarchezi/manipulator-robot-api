// Face.h: interface for the Face class.
//
//////////////////////////////////////////////////////////////////////

#ifndef FACE_H
#define FACE_H

#include "Point.h"

namespace PDC

{

class Face
{
public:
	Face();
	virtual ~Face();
	void SetParameters(Point vertex_1,Point vertex_2,Point vertex_3,long red, long green,long blue);
    void GetParameters(Point &vertex_1, Point &vertex_2, Point &vertex_3,long &red,long &green, long &blue) const;

private:
	long  m_red;
	long  m_green;
	long  m_blue;
	Point m_vertex_1;
	Point m_vertex_2;
	Point m_vertex_3;
};

}

#endif
