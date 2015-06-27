// LinkPosition.cpp: implementation of the LinkPosition class.
//
//////////////////////////////////////////////////////////////////////

#include "LinkPosition.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::LinkPosition::LinkPosition(double jointPosition, double jointVelocity)
{
    _jointPosition = jointPosition;
    _jointVelocity = jointVelocity;
}

PDC::LinkPosition::~LinkPosition()
{
}

double PDC::LinkPosition::GetJointPosition()
{
    return _jointPosition;
}

void PDC::LinkPosition::SetJointPosition(double position)
{
    _jointPosition = position;
}

double PDC::LinkPosition::GetJointVelocity()
{
    return _jointVelocity;
}

void PDC::LinkPosition::SetJointVelocity(double velocity)
{
    _jointVelocity = velocity;
}
