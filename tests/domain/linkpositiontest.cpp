#include <gtest/gtest.h>
#include "LinkPosition.h"

class LinkPositionTest : public ::testing::Test
{

};

TEST_F(LinkPositionTest,objectInstanciatedWithDefaultValues)
{
    PDC::LinkPosition linkPosition(1.2,0.3);
    ASSERT_DOUBLE_EQ(1.2, linkPosition.GetJointPosition());
    ASSERT_DOUBLE_EQ(0.3, linkPosition.GetJointVelocity());
}

TEST_F(LinkPositionTest,getAndSetJointPosition)
{
    PDC::LinkPosition linkPosition(0.0,0.0);
    linkPosition.SetJointPosition(1.25);
    ASSERT_DOUBLE_EQ(1.25, linkPosition.GetJointPosition());
}

TEST_F(LinkPositionTest,getAndSetJointVelocity)
{
    PDC::LinkPosition linkPosition(0.0,0.0);
    linkPosition.SetJointVelocity(0.2);
    ASSERT_DOUBLE_EQ(0.2, linkPosition.GetJointVelocity());
}
