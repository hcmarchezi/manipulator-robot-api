#include <gtest/gtest.h>
#include "LinkTrajectory.h"

class LinkTrajectoryTest : public ::testing::Test
{
public:

};

TEST_F(LinkTrajectoryTest,interpolationFunctionCoefficientsCalculationShouldUseProvidedParameters)
{
    PDC::LinkTrajectory linkTrajectory;

    PDC::LinkTrajectoryParams parameters;
    parameters.initialTime = 1.0;
    parameters.finalTime = 5.0;
    parameters.initialPosition = 1.0;
    parameters.finalPosition = 2.0;
    parameters.initialVelocity = 0.001;
    parameters.finalVelocity = 0.002;

    linkTrajectory.Calculate(parameters);

    EXPECT_DOUBLE_EQ(1.0,linkTrajectory.GetA0());
    EXPECT_DOUBLE_EQ(0.001,linkTrajectory.GetA1());
    EXPECT_DOUBLE_EQ(0.1865,linkTrajectory.GetA2());
    EXPECT_DOUBLE_EQ(-0.0310625,linkTrajectory.GetA3());
}


TEST_F(LinkTrajectoryTest,interpolationFunctionShouldProvideJointPositionAtGivenTime)
{
    PDC::LinkTrajectory linkTrajectory;

    PDC::LinkTrajectoryParams parameters;
    parameters.initialTime = 1.0;
    parameters.finalTime = 5.0;
    parameters.initialPosition = 1.0;
    parameters.finalPosition = 2.5;
    parameters.initialVelocity = 0.01;
    parameters.finalVelocity = 0.015;

    linkTrajectory.Calculate(parameters);

    EXPECT_DOUBLE_EQ(1.0,linkTrajectory.GetJointPositionInTime(1));
    EXPECT_DOUBLE_EQ(2.5,linkTrajectory.GetJointPositionInTime(5));
    EXPECT_DOUBLE_EQ(1.2371875000000001,linkTrajectory.GetJointPositionInTime(2));

}

