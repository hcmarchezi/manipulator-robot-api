// RevoluteLinkType.cpp: implementation of the RevoluteLinkType class.
//
//////////////////////////////////////////////////////////////////////

#include "RevoluteLinkType.h"

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::RevoluteLinkType::RevoluteLinkType(std::string id):LinkType(id)
{
}

PDC::RevoluteLinkType::~RevoluteLinkType()
{
}

double PDC::RevoluteLinkType::GetOffset()
{
    return _offset;
}

void PDC::RevoluteLinkType::SetOffset(double offset)
{
    _offset = offset;
}

void PDC::RevoluteLinkType::CalculateFrame(double variableparam,double (* frame)[4][4])
{
    (*frame)[0][0] = cos(variableparam);
    (*frame)[1][0] = sin(variableparam)*cos(_twist);
    (*frame)[2][0] = sin(variableparam)*sin(_twist);
    (*frame)[3][0] = 0.0;


    (*frame)[0][1] = -sin(variableparam);
    (*frame)[1][1] = cos(variableparam)*cos(_twist);
    (*frame)[2][1] = cos(variableparam)*sin(_twist);
    (*frame)[3][1] = 0.0;

    (*frame)[0][2] = 0.0;
    (*frame)[1][2] = -sin(_twist);
    (*frame)[2][2] = cos(_twist);
    (*frame)[3][2] = 0.0;

    (*frame)[0][3] = _length;
    (*frame)[1][3] = -sin(_twist)*_offset;
    (*frame)[2][3] = cos(_twist)*_offset;
    (*frame)[3][3] = 1.0;
}

std::string PDC::RevoluteLinkType::GetJointType()
{
    return "revolute";
}
