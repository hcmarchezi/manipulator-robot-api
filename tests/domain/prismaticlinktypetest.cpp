
#include <gtest/gtest.h>

#include "PrismaticLinkType.h"

class PrismaticLinkTypeTest : public ::testing::Test
{
public:

};

TEST_F(PrismaticLinkTypeTest,getJointType)
{
    PDC::PrismaticLinkType prismaticLinkType("some-id");
    ASSERT_EQ("prismatic", prismaticLinkType.GetJointType());
}

TEST_F(PrismaticLinkTypeTest,setAndGetJointAngleShouldModifyInstanceAccordingly)
{
    PDC::PrismaticLinkType prismaticLinkType("some-id");
    prismaticLinkType.SetJointAngle(0.0);
    ASSERT_DOUBLE_EQ(0.0, prismaticLinkType.GetJointAngle());
    prismaticLinkType.SetJointAngle(1.25);
    ASSERT_DOUBLE_EQ(1.25, prismaticLinkType.GetJointAngle());
    prismaticLinkType.SetJointAngle(-2.05);
    ASSERT_DOUBLE_EQ(-2.05, prismaticLinkType.GetJointAngle());
}
