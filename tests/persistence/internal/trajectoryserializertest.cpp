#include <gtest/gtest.h>
#include <typeinfo>

#include "jsonxx.h"
#include "trajectory.h"
#include "RobotPosition.h"
#include "internal/trajectoryserializer.h"

//   {
//      "robot_positions" : [
//        { "time_instant":0, "links_positions":[ { "position": 0.21, "velocity":0.0 }, { "position": 0.95, "velocity":0.01 } ] },
//        { "time_instant":5, "links_positions":[ { "position": 0.02, "velocity":0.0 }, { "position": 0.80, "velocity":0.02 } ] },
//        { "time_instant":9, "links_positions":[ { "position": -0.2, "velocity":0.0 }, { "position": 0.50, "velocity":-0.01 } ] }
//      ]
//    }

TEST(TrajectorySerializerTest,serialize)
{
    PDC::Trajectory* trajectory = new PDC::Trajectory();

    PDC::RobotPosition robotPosition1 = PDC::RobotPosition(0.0);
    PDC::LinkPosition linkPosition11 = PDC::LinkPosition(0.0,0.0);
    PDC::LinkPosition linkPosition12 = PDC::LinkPosition(1.0,1.0);
    robotPosition1.AddLinkPosition(linkPosition11);
    robotPosition1.AddLinkPosition(linkPosition12);

    PDC::RobotPosition robotPosition2 = PDC::RobotPosition(5.0);
    PDC::LinkPosition linkPosition21 = PDC::LinkPosition(2.0,2.0);
    PDC::LinkPosition linkPosition22 = PDC::LinkPosition(3.0,3.0);
    robotPosition2.AddLinkPosition(linkPosition21);
    robotPosition2.AddLinkPosition(linkPosition22);

    trajectory->AddRobotPosition(robotPosition1);
    trajectory->AddRobotPosition(robotPosition2);

    jsonxx::Object* json = DMC::Internal::TrajectorySerializer::serialize(trajectory);    

    jsonxx::Object jsonRobotPosition1 = json->get<jsonxx::Array>("robot_positions").get<jsonxx::Object>(0);
    jsonxx::Object jsonRobotPosition2 = json->get<jsonxx::Array>("robot_positions").get<jsonxx::Object>(1);
    ASSERT_DOUBLE_EQ(0.0, jsonRobotPosition1.get<jsonxx::Number>("time_instant"));
    ASSERT_DOUBLE_EQ(5.0, jsonRobotPosition2.get<jsonxx::Number>("time_instant"));

    jsonxx::Object jsonLinkPosition11 = jsonRobotPosition1.get<jsonxx::Array>("links_positions").get<jsonxx::Object>(0);
    jsonxx::Object jsonLinkPosition12 = jsonRobotPosition1.get<jsonxx::Array>("links_positions").get<jsonxx::Object>(1);
    jsonxx::Object jsonLinkPosition21 = jsonRobotPosition2.get<jsonxx::Array>("links_positions").get<jsonxx::Object>(0);
    jsonxx::Object jsonLinkPosition22 = jsonRobotPosition2.get<jsonxx::Array>("links_positions").get<jsonxx::Object>(1);

    ASSERT_DOUBLE_EQ(0.0, jsonLinkPosition11.get<jsonxx::Number>("position"));
    ASSERT_DOUBLE_EQ(0.0, jsonLinkPosition11.get<jsonxx::Number>("velocity"));

    ASSERT_DOUBLE_EQ(1.0, jsonLinkPosition12.get<jsonxx::Number>("position"));
    ASSERT_DOUBLE_EQ(1.0, jsonLinkPosition12.get<jsonxx::Number>("velocity"));

    ASSERT_DOUBLE_EQ(2.0, jsonLinkPosition21.get<jsonxx::Number>("position"));
    ASSERT_DOUBLE_EQ(2.0, jsonLinkPosition21.get<jsonxx::Number>("velocity"));

    ASSERT_DOUBLE_EQ(3.0, jsonLinkPosition22.get<jsonxx::Number>("position"));
    ASSERT_DOUBLE_EQ(3.0, jsonLinkPosition22.get<jsonxx::Number>("velocity"));
}

TEST(TrajectorySerializerTest,deserialize)
{
    jsonxx::Object json;

    jsonxx::Object jsonRobotPosition1;
    jsonRobotPosition1 << "time_instant" << 0.0;

    jsonxx::Object jsonLinkPosition11;
    jsonLinkPosition11 << "position" << 0.0;
    jsonLinkPosition11 << "velocity" << 0.0;
    jsonxx::Object jsonLinkPosition12;
    jsonLinkPosition12 << "position" << 1.0;
    jsonLinkPosition12 << "velocity" << 1.0;
    jsonxx::Array jsonLinksPositions1;
    jsonLinksPositions1 << jsonLinkPosition11 << jsonLinkPosition12;

    jsonRobotPosition1 << "links_positions" << jsonLinksPositions1;

    jsonxx::Object jsonRobotPosition2;
    jsonRobotPosition2 << "time_instant" << 5.0;

    jsonxx::Object jsonLinkPosition21;
    jsonLinkPosition21 << "position" << 2.0;
    jsonLinkPosition21 << "velocity" << 2.0;
    jsonxx::Object jsonLinkPosition22;
    jsonLinkPosition22 << "position" << 3.0;
    jsonLinkPosition22 << "velocity" << 3.0;
    jsonxx::Array jsonLinksPositions2;
    jsonLinksPositions2 << jsonLinkPosition21 << jsonLinkPosition22;

    jsonRobotPosition2 << "links_positions" << jsonLinksPositions2;

    jsonxx::Array jsonRobotPositions;
    jsonRobotPositions << jsonRobotPosition1 << jsonRobotPosition2;
    json << "robot_positions" << jsonRobotPositions;


    PDC::Trajectory* trajectory = DMC::Internal::TrajectorySerializer::deserialize(json);

    PDC::RobotPosition robotPosition1 = trajectory->GetRobotPosition(0);
    ASSERT_DOUBLE_EQ(0.0, robotPosition1.GetInstantTime());

    PDC::LinkPosition linkPosition11 = robotPosition1.GetLinkPosition(0);
    ASSERT_DOUBLE_EQ(0.0, linkPosition11.GetJointPosition());
    ASSERT_DOUBLE_EQ(0.0, linkPosition11.GetJointVelocity());

    PDC::LinkPosition linkPosition12 = robotPosition1.GetLinkPosition(1);
    ASSERT_DOUBLE_EQ(1.0, linkPosition12.GetJointPosition());
    ASSERT_DOUBLE_EQ(1.0, linkPosition12.GetJointVelocity());

    PDC::RobotPosition robotPosition2 = trajectory->GetRobotPosition(1);
    ASSERT_DOUBLE_EQ(5.0, robotPosition2.GetInstantTime());

    PDC::LinkPosition linkPosition21 = robotPosition2.GetLinkPosition(0);
    ASSERT_DOUBLE_EQ(2.0, linkPosition21.GetJointPosition());
    ASSERT_DOUBLE_EQ(2.0, linkPosition21.GetJointVelocity());

    PDC::LinkPosition linkPosition22 = robotPosition2.GetLinkPosition(1);
    ASSERT_DOUBLE_EQ(3.0, linkPosition22.GetJointPosition());
    ASSERT_DOUBLE_EQ(3.0, linkPosition22.GetJointVelocity());

    delete trajectory;
}
