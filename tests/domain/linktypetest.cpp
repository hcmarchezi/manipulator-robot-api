#include <gtest/gtest.h>
#include "LinkType.h"
#include "geometry.h"
#include "concretelinktype.h"

TEST(LinkTypeTest, setAndGetTwist)
{
    PDC::LinkType* linkType = new ConcreteLinkType("");
    linkType->SetTwist(0.0);
    ASSERT_DOUBLE_EQ(0.0, linkType->GetTwist());
    linkType->SetTwist(2.2);
    ASSERT_DOUBLE_EQ(2.2, linkType->GetTwist());
    linkType->SetTwist(-1.4);
    ASSERT_DOUBLE_EQ(-1.4, linkType->GetTwist());
    delete linkType;
}

TEST(LinkTypeTest, setAndGetLength)
{
    PDC::LinkType* linkType = new ConcreteLinkType("");
    linkType->SetLength(0.0);
    ASSERT_DOUBLE_EQ(0.0, linkType->GetLength());
    linkType->SetLength(2.0);
    ASSERT_DOUBLE_EQ(2.0, linkType->GetLength());
    delete linkType;
}

TEST(LinkTypeTest, setAndGetId)
{
    PDC::LinkType* linkType = new ConcreteLinkType("some-id");
    ASSERT_EQ("some-id",linkType->GetId());
}

TEST(LinkTypeTest, setAndGetRole)
{
    PDC::LinkType* linkType = new ConcreteLinkType("");
    linkType->SetRole(PDC::LinkType::BASE);
    ASSERT_EQ("base",linkType->GetRole());
    linkType->SetRole(PDC::LinkType::LINK);
    ASSERT_EQ("link",linkType->GetRole());
    linkType->SetRole(PDC::LinkType::END_EFFECTOR);
    ASSERT_EQ("end effector",linkType->GetRole());
}

TEST(LinkTypeTest, setAndGetGeometrySource)
{
    PDC::LinkType* linkType = new ConcreteLinkType("");
    linkType->SetGeometrySource(PDC::GeometrySource("geometry-source.ext","name"));
    ASSERT_EQ(PDC::GeometrySource("geometry-source.ext","name"),linkType->GetGeometrySource());
}

TEST(LinkTypeTest, setAndGetGeometry)
{
    PDC::LinkType* linkType = new ConcreteLinkType("");
    PDC::Geometry* geometry = new PDC::Geometry();
    linkType->SetGeometry(geometry);
    ASSERT_EQ(geometry, linkType->GetGeometry());
}


TEST(LinkTypeTest, presenceOfCalculateFrameMethod)
{
    PDC::LinkType* linkType = new ConcreteLinkType("");
    double jointMove = 0.0;
    double frame[4][4];
    linkType->CalculateFrame(jointMove,&frame);
}

/*

TEST(LinkTypeTest,jointRestrictionShouldReturnThePreviouslySetJointRestriction)
{
    ConcreteLinkType linkType;
    linkType.SetJointRestriction(-0.25,0.85);
    double lowest, highest;
    linkType.GetJointRestriction(lowest,highest);
    ASSERT_EQ(-0.25,lowest);
    ASSERT_EQ(0.85,highest);
}
*/
