#include <gtest/gtest.h>
#include "Robot.h"

class RobotTest : public ::testing::Test
{
protected:
    PDC::Link* createLink()
    {
        PDC::Link* link = new PDC::Link();
        return link;
    }
};

TEST_F(RobotTest,setPoseShouldSetPositionAndOrientationToRobotLinkChainBase)
{
    PDC::Robot robot;
    PDC::Pose pose;
    pose[0][0] = 0;  pose[0][1] = 1;  pose[0][2] = 2;  pose[0][3] = 3;
    pose[1][0] = 4;  pose[1][1] = 5;  pose[1][2] = 6;  pose[1][3] = 7;
    pose[2][0] = 8;  pose[2][1] = 9;  pose[2][2] = 10; pose[2][3] = 11;
    pose[3][0] = 12; pose[3][1] = 13; pose[3][2] = 14; pose[3][3] = 15;
    robot.SetPose(pose);
    PDC::Pose returnedPose;
    robot.GetPose(returnedPose);
    ASSERT_TRUE(PDC::PoseFunctions::equal(pose,returnedPose));
}


TEST_F(RobotTest,addLinkToRobotLinkChain)
{
    PDC::Robot robot;
    PDC::Link* link = createLink();
    robot.AppendLink(link);
    PDC::Link* returnedLink = robot.GetLink(0);
    ASSERT_EQ(link,returnedLink);
}

TEST_F(RobotTest,appendLinkShouldAppendToTheEndOfRobotLinkChain)
{
    PDC::Robot robot;
    robot.AppendLink(createLink());
    robot.AppendLink(createLink());
    robot.AppendLink(createLink());
    PDC::Link* link = createLink();
    robot.AppendLink(link);
    PDC::Link* returnedLink = robot.GetLink(3);
    ASSERT_EQ(link,returnedLink);
}

TEST_F(RobotTest,insertLinkShouldIncludeLinkInRobotLinkChainInRightPosition)
{
    PDC::Robot robot;
    robot.AppendLink(createLink());
    robot.AppendLink(createLink());
    robot.AppendLink(createLink());
    PDC::Link* link = createLink();
    robot.InsertLink(1,link);
    PDC::Link* returnedLink = robot.GetLink(1);
    ASSERT_EQ(link,returnedLink);
}


TEST_F(RobotTest,linkCountShouldReturnTheNumberOfLinksAttachedInTheChain)
{
    PDC::Robot robot;
    robot.AppendLink(createLink());
    robot.AppendLink(createLink());
    robot.AppendLink(createLink());
    robot.AppendLink(createLink());
    ASSERT_EQ(4, robot.LinkCount());
}

TEST_F(RobotTest,removeLinkShouldRemoveTheIthLinkOfRobotChain)
{
    PDC::Robot robot;
    PDC::Link* link1 = createLink();
    PDC::Link* link2 = createLink();
    PDC::Link* link3 = createLink();
    PDC::Link* link4 = createLink();
    robot.AppendLink(link1);
    robot.AppendLink(link2);
    robot.AppendLink(link3);
    robot.AppendLink(link4);
    robot.RemoveLink((unsigned int)2);
    ASSERT_EQ(link1, robot.GetLink(0));
    ASSERT_EQ(link2, robot.GetLink(1));
    ASSERT_EQ(link4, robot.GetLink(2));
}



