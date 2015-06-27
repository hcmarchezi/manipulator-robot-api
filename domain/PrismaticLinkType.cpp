// PrismaticLinkType.cpp: implementation of the PrismaticLinkType class.
//
//////////////////////////////////////////////////////////////////////

#include "PrismaticLinkType.h"

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::PrismaticLinkType::PrismaticLinkType(std::string id):LinkType(id)
{
}

PDC::PrismaticLinkType::~PrismaticLinkType()
{
}

double PDC::PrismaticLinkType::GetJointAngle()
{
    return _jointAngle;
}

void PDC::PrismaticLinkType::SetJointAngle(double angle)
{
    _jointAngle = angle;
}

void PDC::PrismaticLinkType::CalculateFrame(double variableparam,double (* frame)[4][4])
{
    // In the prismatic link type
    // the parameters link length, link twist and joint angle
    // are fixed while the link offset is variable

    (*frame)[0][0] = cos(_jointAngle);
    (*frame)[1][0] = sin(_jointAngle)*cos(_twist);
    (*frame)[2][0] = sin(_jointAngle)*sin(_twist);
    (*frame)[3][0] = 0.0;

    (*frame)[0][1] = -sin(_jointAngle);
    (*frame)[1][1] =  cos(_jointAngle)*cos(_twist);
    (*frame)[2][1] =  cos(_jointAngle)*sin(_twist);
    (*frame)[3][1] = 0.0;

    (*frame)[0][2] = 0.0;
    (*frame)[1][2] = -sin(_twist);
    (*frame)[2][2] =  cos(_twist);
    (*frame)[3][2] = 0.0;

    (*frame)[0][3] = _length;
    (*frame)[1][3] = -sin(_twist)*variableparam;
    (*frame)[2][3] =  cos(_twist)*variableparam;
    (*frame)[3][3] = 1.0;
}

std::string PDC::PrismaticLinkType::GetJointType()
{
    return "prismatic";
}
