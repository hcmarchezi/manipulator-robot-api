// LinkPosition.h: interface for the LinkPosition class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LINKPOSITION_H
#define LINKPOSITION_H

namespace PDC
{

class LinkPosition
{
public:
    LinkPosition(double jointPosition,double jointVelocity);
	virtual ~LinkPosition();
    void SetJointVelocity(double velocity);
    double GetJointVelocity();
    void SetJointPosition(double position);
    double GetJointPosition();

private:
    double _jointPosition;
    double _jointVelocity;
};

}

#endif
