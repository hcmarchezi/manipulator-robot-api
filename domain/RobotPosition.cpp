// RobotPosition.cpp: implementation of the RobotPosition class.
//
//////////////////////////////////////////////////////////////////////

#include "RobotPosition.h"

using namespace PDC;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::RobotPosition::RobotPosition(double instantTime)
{
    _timeInstant = instantTime;
}

PDC::RobotPosition::~RobotPosition()
{
}

double PDC::RobotPosition::GetInstantTime() const
{
    return _timeInstant;
}

void PDC::RobotPosition::SetInstantTime(double time)
{
    _timeInstant = time;
}

void PDC::RobotPosition::AddLinkPosition(const LinkPosition &linkPosition)
{
    _linkPositions.push_back(linkPosition);
}

const PDC::LinkPosition& PDC::RobotPosition::GetLinkPosition(int linkNumber) const
{
    return _linkPositions[linkNumber];
}

const unsigned int PDC::RobotPosition::GetLinkPositionsSize() const
{
    return _linkPositions.size();
}
