#ifndef PARTIALROBOTTRAJECTORY_H
#define PARTIALROBOTTRAJECTORY_H

#include "RobotPosition.h"
#include "LinkTrajectory.h"

#include <vector>

namespace PDC
{

class PartialRobotTrajectory
{
public:
    PartialRobotTrajectory();
    void Calculate(PDC::RobotPosition initialRobotPosition,PDC::RobotPosition finalRobotPosition);
    double GetInitialTime() const;
    double GetFinalTime() const;
    int GetLinkTrajectorySize();
    PDC::LinkTrajectory GetLinkTrajectory(int order);

protected:
    double _initialTime, _finalTime;
    std::vector<PDC::LinkTrajectory> _linkTrajectories;
};

}

#endif // PARTIALROBOTTRAJECTORY_H
