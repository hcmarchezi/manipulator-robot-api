#include <gtest/gtest.h>
#include "RobotPosition.h"

class RobotPositionTest : public ::testing::Test
{

};

TEST_F(RobotPositionTest,objectInstanciationWithInstantTime)
{
    PDC::RobotPosition robotPosition(5.5);
    ASSERT_DOUBLE_EQ(5.5, robotPosition.GetInstantTime());
}

TEST_F(RobotPositionTest,setAndGetTimeInstant)
{
    PDC::RobotPosition robotPosition(0.0);
    robotPosition.SetInstantTime(12.5);
    ASSERT_DOUBLE_EQ(12.5, robotPosition.GetInstantTime());
}

TEST_F(RobotPositionTest,addAndGetLinkPositions)
{
    PDC::RobotPosition robotPosition(0.0);
    robotPosition.AddLinkPosition(PDC::LinkPosition(1.0,0.1));
    robotPosition.AddLinkPosition(PDC::LinkPosition(2.5,0.2));
    robotPosition.AddLinkPosition(PDC::LinkPosition(4.0,0.4));

    PDC::LinkPosition linkPosition1 = robotPosition.GetLinkPosition(0);
    ASSERT_DOUBLE_EQ(1.0, linkPosition1.GetJointPosition());
    ASSERT_DOUBLE_EQ(0.1, linkPosition1.GetJointVelocity());

    PDC::LinkPosition linkPosition2 = robotPosition.GetLinkPosition(1);
    ASSERT_DOUBLE_EQ(2.5, linkPosition2.GetJointPosition());
    ASSERT_DOUBLE_EQ(0.2, linkPosition2.GetJointVelocity());

    PDC::LinkPosition linkPosition3 = robotPosition.GetLinkPosition(2);
    ASSERT_DOUBLE_EQ(4.0, linkPosition3.GetJointPosition());
    ASSERT_DOUBLE_EQ(0.4, linkPosition3.GetJointVelocity());
}
