#include <gtest/gtest.h>
#include "RobotPosition.h"
#include "LinkTrajectory.h"
#include "PartialRobotTrajectory.h"

#include<list>

class PartialRobotTrajectoryTest : public ::testing::Test
{
public:

};

TEST_F(PartialRobotTrajectoryTest,calculateTrajectoryShouldCalculateLinkTrajectoriesFromInitialToFinalRobotPosition)
{
    PDC::RobotPosition initialRobotPosition = PDC::RobotPosition(5.0);
    initialRobotPosition.AddLinkPosition(PDC::LinkPosition(0.0,0.0));
    initialRobotPosition.AddLinkPosition(PDC::LinkPosition(0.1,0.0));

    PDC::RobotPosition finalRobotPosition = PDC::RobotPosition(10.0);
    finalRobotPosition.AddLinkPosition(PDC::LinkPosition(0.0,0.0));
    finalRobotPosition.AddLinkPosition(PDC::LinkPosition(0.5,0.01));

    PDC::PartialRobotTrajectory partialRobotTrajectory;
    partialRobotTrajectory.Calculate(initialRobotPosition,finalRobotPosition);

    ASSERT_DOUBLE_EQ(5.0,partialRobotTrajectory.GetInitialTime());
    ASSERT_DOUBLE_EQ(10.0,partialRobotTrajectory.GetFinalTime());
    ASSERT_EQ(2,partialRobotTrajectory.GetLinkTrajectorySize());

    PDC::LinkTrajectory linkTrajectory1 = partialRobotTrajectory.GetLinkTrajectory(0);
    EXPECT_DOUBLE_EQ(0.0, linkTrajectory1.GetA0());
    EXPECT_DOUBLE_EQ(0.0, linkTrajectory1.GetA1());
    EXPECT_DOUBLE_EQ(0.0, linkTrajectory1.GetA2());
    EXPECT_DOUBLE_EQ(0.0, linkTrajectory1.GetA3());

    PDC::LinkTrajectory linkTrajectory2 = partialRobotTrajectory.GetLinkTrajectory(1);
    EXPECT_DOUBLE_EQ(0.1, linkTrajectory2.GetA0());
    EXPECT_DOUBLE_EQ(0.0, linkTrajectory2.GetA1());
    EXPECT_DOUBLE_EQ(0.045999999999999999, linkTrajectory2.GetA2());
    EXPECT_DOUBLE_EQ(-0.0060000000000000001, linkTrajectory2.GetA3());

}

