// RobotPosition.h: interface for the RobotPosition class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ROBOTPOSITION_H
#define ROBOTPOSITION_H

#include<vector>
#include "LinkPosition.h"

namespace PDC
{

class RobotPosition
{
private:
    double  _timeInstant;
    std::vector<PDC::LinkPosition> _linkPositions;

public:
    RobotPosition(double instantTime);
	virtual ~RobotPosition();

    void AddLinkPosition (const PDC::LinkPosition& linkPosition);
    const LinkPosition& GetLinkPosition(int linkNumber) const;
    const unsigned int GetLinkPositionsSize() const;

    double  GetInstantTime() const;
	void    SetInstantTime(double time);
};

}

#endif
