#include "LinkTrajectory.h"

#include<math.h>

PDC::LinkTrajectory::LinkTrajectory()
{    
}

void PDC::LinkTrajectory::Calculate(LinkTrajectoryParams params)
{
    // Avoid division by zero
    if (params.initialTime == params.finalTime)
    {
        _a0 = _a1 = _a2 = _a3 = 0;
        return;
    }

    _timeOffset = params.initialTime;
    _a0 = params.initialPosition;
    _a1 = params.initialVelocity;
    _a2 = (3.0)/pow((params.finalTime - params.initialTime),2.0)*(params.finalPosition - params.initialPosition) - (2.0)/(params.finalTime - params.initialTime)*params.initialVelocity - (1.0)/(params.finalTime - params.initialTime)*params.finalVelocity;
    _a3 = -(2.0)/pow((params.finalTime - params.initialTime),3.0)*(params.finalPosition - params.initialPosition) + (1.0)/pow((params.finalTime - params.initialTime),2.0)*(params.finalVelocity + params.initialVelocity);
}

double PDC::LinkTrajectory::GetA0()
{
    return _a0;
}

double PDC::LinkTrajectory::GetA1()
{
    return _a1;
}

double PDC::LinkTrajectory::GetA2()
{
    return _a2;
}

double PDC::LinkTrajectory::GetA3()
{
    return _a3;
}

double PDC::LinkTrajectory::GetJointPositionInTime(double time)
{
    time = time - _timeOffset;

    double time_pow_2 = time*time;
    double time_pow_3 = time_pow_2 * time;

    double position = _a3*time_pow_3 + _a2*time_pow_2 + _a1*time + _a0;

    return position;
}
