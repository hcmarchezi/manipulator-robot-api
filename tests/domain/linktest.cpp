#include <gtest/gtest.h>
#include "Link.h"
#include "LinkType.h"
#include "concretelinktype.h"

class LinkTest : public ::testing::Test
{
public:
    PDC::LinkType* createLinkType()
    {
        return new ConcreteLinkType("");
    }
};

TEST_F(LinkTest,instanciateShouldCreateObjectWithDefaultValues)
{
    PDC::Link link;
    ASSERT_DOUBLE_EQ(0.0, link.GetJointMove());
}


TEST_F(LinkTest,setAndGetJointMoveShouldWriteAndReadFromLink)
{
    PDC::Link link;
    link.SetJointMove(0.5);
    ASSERT_DOUBLE_EQ(0.5, link.GetJointMove());
    link.SetJointMove(0.0);
    ASSERT_DOUBLE_EQ(0.0, link.GetJointMove());
    link.SetJointMove(-2.5);
    ASSERT_DOUBLE_EQ(-2.5, link.GetJointMove());
}


TEST_F(LinkTest,setAndGetLinkType)
{
    PDC::LinkType* linkType = createLinkType();
    PDC::Link link;
    link.SetLinkType(linkType);
    ASSERT_EQ(link.GetLinkType(),linkType);
    delete linkType;
}



