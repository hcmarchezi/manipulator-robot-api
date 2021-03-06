#include <gtest/gtest.h>
#include "linktypepersistence.h"
#include "PrismaticLinkType.h"
#include "RevoluteLinkType.h"
#include "filehelper.h"

#include <fstream>

class LinkTypePersistenceTest : public ::testing::Test
{
public:    
    LinkTypePersistenceTest()
    {
        _linkType = NULL;
    }
    PDC::LinkType* GetLinkType()
    {
        if (_linkType == NULL)
        {
            _linkType = new PDC::PrismaticLinkType("fake-link-type");
            _linkType->SetLength(10.0);
            _linkType->SetTwist(5.0);
            _linkType->SetRole(PDC::LinkType::BASE);
            _linkType->SetJointAngle(0.2);
            _linkType->SetGeometrySource(PDC::GeometrySource("geometry.3ds","objname"));

            double geometryPose[4][4] = {
                                            { 1.0, 2.0, 3.0, 4.0 },
                                            { 5.0, 6.0, 7.0, 8.0 },
                                            { 9.0, 10.0, 11.0, 12.0 },
                                            { 13.0, 14.0, 15.0, 16.0 }
                                        };
            _linkType->SetGeometryPose(geometryPose);

        }
        return _linkType;
    }
protected:
    UTILS::FileHelper _fileHelper;
    PDC::PrismaticLinkType* _linkType;
};

TEST_F(LinkTypePersistenceTest,saveLinkTypeShouldCreateItsCorrespondingJsonFileAndSaveContents)
{
    PDC::LinkType* linkType = GetLinkType();
    DMC::LinkTypePersistence::Save(linkType);
    ASSERT_TRUE(_fileHelper.Exists("fake-link-type.linktype"));
}

TEST_F(LinkTypePersistenceTest,loadLinkTypeByIdShouldLoadFromCorrespondingFileAndRecoverObject)
{
    PDC::LinkType* linkType = DMC::LinkTypePersistence::Load("fake-link-type");
    PDC::LinkType* expectedLinkType = GetLinkType();
    ASSERT_TRUE(linkType != NULL);
    ASSERT_STREQ(expectedLinkType->GetId().c_str(),linkType->GetId().c_str());
}

TEST_F(LinkTypePersistenceTest,removeLinkTypeShouldRemoveItsCorrespondingJsonFile)
{
    PDC::LinkType* linkType = GetLinkType();
    DMC::LinkTypePersistence::Remove(linkType);
    ASSERT_FALSE(_fileHelper.Exists("fake-link-type.linktype"));
}
