#include <gtest/gtest.h>
#include "trajectory.h"
#include "RobotPosition.h"
#include "PartialRobotTrajectory.h"

class TrajectoryTest : public ::testing::Test
{
public:

};

TEST_F(TrajectoryTest,addAndGetRobotPosition)
{
    PDC::Trajectory robotTrajectory;
    robotTrajectory.AddRobotPosition(PDC::RobotPosition(0.0));
    robotTrajectory.AddRobotPosition(PDC::RobotPosition(5.0));
    robotTrajectory.AddRobotPosition(PDC::RobotPosition(12.0));
    robotTrajectory.AddRobotPosition(PDC::RobotPosition(10.0));

    ASSERT_DOUBLE_EQ(0.0, robotTrajectory.GetRobotPosition(0).GetInstantTime());
    ASSERT_DOUBLE_EQ(5.0, robotTrajectory.GetRobotPosition(1).GetInstantTime());
    ASSERT_DOUBLE_EQ(10.0, robotTrajectory.GetRobotPosition(2).GetInstantTime());
    ASSERT_DOUBLE_EQ(12.0, robotTrajectory.GetRobotPosition(3).GetInstantTime());
}

TEST_F(TrajectoryTest,trajectoryCalculation)
{
    PDC::Trajectory robotTrajectory;
    PDC::RobotPosition robotPosition1 = PDC::RobotPosition(2.0);
    PDC::RobotPosition robotPosition2 = PDC::RobotPosition(4.0);
    PDC::RobotPosition robotPosition3 = PDC::RobotPosition(6.0);

    robotTrajectory.AddRobotPosition(robotPosition1);
    robotTrajectory.AddRobotPosition(robotPosition2);
    robotTrajectory.AddRobotPosition(robotPosition3);

    robotTrajectory.Calculate();

    ASSERT_EQ(2, robotTrajectory.GetPartialRobotTrajectoriesSize());

    PDC::PartialRobotTrajectory partial1 = robotTrajectory.GetPartialRobotTrajectory(0);
    EXPECT_DOUBLE_EQ(2.0,partial1.GetInitialTime());
    EXPECT_DOUBLE_EQ(4.0,partial1.GetFinalTime());

    PDC::PartialRobotTrajectory partial2 = robotTrajectory.GetPartialRobotTrajectory(1);
    EXPECT_DOUBLE_EQ(4.0,partial2.GetInitialTime());
    EXPECT_DOUBLE_EQ(6.0,partial2.GetFinalTime());
}


TEST_F(TrajectoryTest,linkPositionInTimeCalculation)
{
    PDC::Trajectory robotTrajectory;
    PDC::RobotPosition robotPosition1 = PDC::RobotPosition(2.0);
    robotPosition1.AddLinkPosition(PDC::LinkPosition(0.0,0.0));
    PDC::RobotPosition robotPosition2 = PDC::RobotPosition(4.0);
    robotPosition2.AddLinkPosition(PDC::LinkPosition(0.5,0.01));
    PDC::RobotPosition robotPosition3 = PDC::RobotPosition(6.0);
    robotPosition3.AddLinkPosition(PDC::LinkPosition(1.0,0.02));

    robotTrajectory.AddRobotPosition(robotPosition1);
    robotTrajectory.AddRobotPosition(robotPosition2);
    robotTrajectory.AddRobotPosition(robotPosition3);

    robotTrajectory.Calculate();

    EXPECT_DOUBLE_EQ(0.0, robotTrajectory.GetLinkPositionInTime(0,2.0));
    EXPECT_DOUBLE_EQ(0.5, robotTrajectory.GetLinkPositionInTime(0,4.0));
    EXPECT_DOUBLE_EQ(1.0, robotTrajectory.GetLinkPositionInTime(0,6.0));

    EXPECT_DOUBLE_EQ(0.2475, robotTrajectory.GetLinkPositionInTime(0,3.0));
    EXPECT_DOUBLE_EQ(0.7475, robotTrajectory.GetLinkPositionInTime(0,5.0));

}

TEST_F(TrajectoryTest,removeRobotPosition)
{
    PDC::Trajectory robotTrajectory;
    PDC::RobotPosition robotPosition1 = PDC::RobotPosition(2.0);
    PDC::RobotPosition robotPosition2 = PDC::RobotPosition(4.0);
    PDC::RobotPosition robotPosition3 = PDC::RobotPosition(6.0);

    robotTrajectory.AddRobotPosition(robotPosition1);
    robotTrajectory.AddRobotPosition(robotPosition2);
    robotTrajectory.AddRobotPosition(robotPosition3);

    robotTrajectory.RemoveRobotPosition(1);

    ASSERT_EQ(2,robotTrajectory.GetRobotPositionCount());
    ASSERT_DOUBLE_EQ(2.0,robotTrajectory.GetRobotPosition(0).GetInstantTime());
    ASSERT_DOUBLE_EQ(6.0,robotTrajectory.GetRobotPosition(1).GetInstantTime());
}

