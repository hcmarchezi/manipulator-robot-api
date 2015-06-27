#include <gtest/gtest.h>

#include "RevoluteLinkType.h"

class RevoluteLinkTypeTest : public ::testing::Test
{
public:

};

TEST_F(RevoluteLinkTypeTest,getJointType)
{
    PDC::RevoluteLinkType revoluteLinkType("some-id");
    ASSERT_EQ("revolute", revoluteLinkType.GetJointType());
}

TEST_F(RevoluteLinkTypeTest,setAndGetOffsetShouldModifyInstanceAccordingly)
{
    PDC::RevoluteLinkType revoluteLinkType("some-id");
    revoluteLinkType.SetOffset(0.0);
    ASSERT_DOUBLE_EQ(0.0, revoluteLinkType.GetOffset());
    revoluteLinkType.SetOffset(1.25);
    ASSERT_DOUBLE_EQ(1.25, revoluteLinkType.GetOffset());
    revoluteLinkType.SetOffset(-2.05);
    ASSERT_DOUBLE_EQ(-2.05, revoluteLinkType.GetOffset());
}
