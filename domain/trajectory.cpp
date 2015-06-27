#include "trajectory.h"

PDC::Trajectory::Trajectory()
{
}

bool compareRobotPosition(PDC::RobotPosition position1,PDC::RobotPosition position2)
{
    return (position1.GetInstantTime() < position2.GetInstantTime());
}

void PDC::Trajectory::AddRobotPosition(PDC::RobotPosition robotPosition)
{
    _robotPositions.push_back(robotPosition);
    _robotPositions.sort(compareRobotPosition);
}

void PDC::Trajectory::RemoveRobotPosition(int order)
{
    std::list<PDC::RobotPosition>::iterator iterator = _robotPositions.begin();
    for (int index=0; index < order; index++)
    {
        iterator++;
    }
    _robotPositions.erase(iterator);
}


const PDC::RobotPosition& PDC::Trajectory::GetRobotPosition(int order)
{
    std::list<PDC::RobotPosition>::iterator iterator = _robotPositions.begin();
    for(int index=0;index < order;index++)
    {
        iterator++;
    }
    return *iterator;
}

int PDC::Trajectory::GetRobotPositionCount()
{
    return _robotPositions.size();
}

void PDC::Trajectory::Calculate()
{
    if (_robotPositions.size() < 2)
    {
        return;
    }

    for(unsigned int index = 1; index < _robotPositions.size(); index++)
    {
        PDC::RobotPosition initialRobotPosition = GetRobotPosition(index-1);
        PDC::RobotPosition finalRobotPosition   = GetRobotPosition(index);
        PDC::PartialRobotTrajectory partialTrajectory = PDC::PartialRobotTrajectory();
        partialTrajectory.Calculate(initialRobotPosition,finalRobotPosition);
        _partialRobotTrajectories.push_back(partialTrajectory);
    }
}

unsigned int PDC::Trajectory::GetPartialRobotTrajectoriesSize()
{
    return _partialRobotTrajectories.size();
}

PDC::PartialRobotTrajectory PDC::Trajectory::GetPartialRobotTrajectory(int order)
{
    return _partialRobotTrajectories[order];
}

double PDC::Trajectory::GetLinkPositionInTime(int order,double time)
{
    for(unsigned int index=0; index < _partialRobotTrajectories.size(); index++)
    {
        PDC::PartialRobotTrajectory partialTrajectory = _partialRobotTrajectories[index];
        if ((time >= partialTrajectory.GetInitialTime() && time <= partialTrajectory.GetFinalTime())||(index == _partialRobotTrajectories.size()-1))
        {
            return partialTrajectory.GetLinkTrajectory(order).GetJointPositionInTime(time);
        }
    }
    return 0.0;
}
