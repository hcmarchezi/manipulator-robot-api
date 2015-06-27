#include "PartialRobotTrajectory.h"

PDC::PartialRobotTrajectory::PartialRobotTrajectory()
{
}

void PDC::PartialRobotTrajectory::Calculate(PDC::RobotPosition initialRobotPosition,PDC::RobotPosition finalRobotPosition)
{
    // Should not accept two robot positions with different link position array sizes
    if (initialRobotPosition.GetLinkPositionsSize() != finalRobotPosition.GetLinkPositionsSize())
    {
        return;
    }

    _initialTime = initialRobotPosition.GetInstantTime();
    _finalTime   = finalRobotPosition.GetInstantTime();

    unsigned int linkPositionsSize = initialRobotPosition.GetLinkPositionsSize();
    for(unsigned int index=0; index < linkPositionsSize; index++)
    {
        PDC::LinkTrajectory linkTrajectory = PDC::LinkTrajectory();
        PDC::LinkPosition initialLinkPosition = initialRobotPosition.GetLinkPosition(index);
        PDC::LinkPosition finalLinkPosition = finalRobotPosition.GetLinkPosition(index);

        PDC::LinkTrajectoryParams params;
        params.initialTime = initialRobotPosition.GetInstantTime();
        params.finalTime   = finalRobotPosition.GetInstantTime();
        params.initialPosition = initialLinkPosition.GetJointPosition();
        params.finalPosition   = finalLinkPosition.GetJointPosition();
        params.initialVelocity = initialLinkPosition.GetJointVelocity();
        params.finalVelocity   = finalLinkPosition.GetJointVelocity();

        linkTrajectory.Calculate(params);

        _linkTrajectories.push_back(linkTrajectory);
    }

}

double PDC::PartialRobotTrajectory::GetInitialTime() const
{
    return _initialTime;
}


double PDC::PartialRobotTrajectory::GetFinalTime() const
{
    return _finalTime;
}

int PDC::PartialRobotTrajectory::GetLinkTrajectorySize()
{
    return _linkTrajectories.size();
}

PDC::LinkTrajectory PDC::PartialRobotTrajectory::GetLinkTrajectory(int order)
{
    return _linkTrajectories[order];
}
