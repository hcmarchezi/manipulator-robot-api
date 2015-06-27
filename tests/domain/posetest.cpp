#include <gtest/gtest.h>
#include "pose.h"

class PoseTest : public ::testing::Test
{
public:
    void fillMatrix(double (*matrix)[4][4]);
    void zeroMatrix(double (*matrix)[4][4]);
};

TEST_F(PoseTest,equalOperatorShouldCompareEachMatrixPosition)
{    
    PDC::Pose pose1;
    fillMatrix(&pose1);

    PDC::Pose pose2;
    zeroMatrix(&pose2);

    PDC::Pose pose3;
    fillMatrix(&pose3);

    ASSERT_FALSE(PDC::PoseFunctions::equal(pose1, pose2));
    ASSERT_TRUE (PDC::PoseFunctions::equal(pose1, pose3));
}

void PoseTest::fillMatrix(double (*matrix)[4][4])
{
    for(unsigned int line=0; line < 4; line++)
    {
        for(unsigned int column=0; column < 4;column++)
        {
            (*matrix)[line][column] = line*4 + column;
        }
    }
}

void PoseTest::zeroMatrix(double (*matrix)[4][4])
{
    for(unsigned int line=0; line < 4; line++)
    {
        for(unsigned int column=0; column < 4;column++)
        {
            (*matrix)[line][column] = 0.0;
        }
    }
}
