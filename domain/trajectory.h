#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "RobotPosition.h"
#include "PartialRobotTrajectory.h"

#include <list>
#include <vector>

namespace PDC
{

class Trajectory
{
public:
    Trajectory();
    void AddRobotPosition(PDC::RobotPosition robotPosition);
    void RemoveRobotPosition(int order);
    const PDC::RobotPosition& GetRobotPosition(int order);
    int GetRobotPositionCount();
    void Calculate();
    unsigned int GetPartialRobotTrajectoriesSize();
    PDC::PartialRobotTrajectory GetPartialRobotTrajectory(int order);
    double GetLinkPositionInTime(int order, double time);


private:
    std::list<PDC::RobotPosition> _robotPositions;
    std::vector<PDC::PartialRobotTrajectory> _partialRobotTrajectories;
};

}

#endif // TRAJECTORY_H
