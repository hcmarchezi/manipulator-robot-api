#ifndef LINKTRAJECTORY_H
#define LINKTRAJECTORY_H

namespace PDC
{

    typedef struct
    {
        double initialTime;
        double finalTime;
        double initialPosition;
        double finalPosition;
        double initialVelocity;
        double finalVelocity;
    } LinkTrajectoryParams;

class LinkTrajectory
{
public:
    LinkTrajectory();

    void Calculate(PDC::LinkTrajectoryParams params);

    double GetA0();
    double GetA1();
    double GetA2();
    double GetA3();
    double GetJointPositionInTime(double time);

private:
    // Trajectory funtion in time: f(t) = _a3 t³ + _a2 t² + _a1 t + _a0
    double _a0;
    double _a1;
    double _a2;
    double _a3;
    // Subtract time parameter by this - interpolation formula
    // only considers trajectory begining with t=0 regardless
    // of non-zero initial time
    double _timeOffset;
};

}

#endif // LINKTRAJECTORY_H
