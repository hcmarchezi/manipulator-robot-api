#include<gtest/gtest.h>

#include "Robot.h"
#include "robotpersistence.h"
#include "RevoluteLinkType.h"
#include "PrismaticLinkType.h"
#include "trajectory.h"

#include <fstream>
#include <sstream>

/*

{
  "robot" :
  {
    "links" : [ { "joint_move":0.85, "link_type_id":"robot-base" }, { "joint_move":0.5, "link_type_id":"robot-arm" } ]
  },
  "trajectory" :
  {
    "robot_positions" : [
        { "time_instant":0, "links_positions":[ { "position": 0.21, "velocity":0.0 }, { "position": 0.95, "velocity":0.01 } ] },
        { "time_instant":5, "links_positions":[ { "posiiton": 0.02, "velocity":0.0 }, { "position": 0.80, "velocity":0.02 } ] },
        { "time_instant":9, "links_positions":[ { "position": -0.2, "velocity":0.0 }, { "position": 0.50, "velocity":-0.01 } ] }
    ]
  },
  "link_types" : [
        { "id":"robot-base", "role":"base",        "joint_type":"revolute",  "length":2.5, "twist":0.1, "joint_offset":0.7, "geometry_source":"robot.3ds:base" },
        { "id":"robot-arm",  "role":"link",        "joint_type":"revolute",  "length":3.0, "twist":0.3, "joint_offset":0.5, "geometry_source":"robot.3ds:arm" },
        { "id":"robot-tool", "role":"end-effector","joint_type":"prismatic", "length":0.7, "twist":0.2, "joint_angle":0.8,  "geometry_source":"robot.3ds:welding" }
  ]
}

*/

namespace DMC
{
class RobotPersistenceExposer : public DMC::RobotPersistence
{
public:
    static void Serialize(PDC::Robot* robot,std::string* robotJson) { RobotPersistence::Serialize(robot,robotJson); }
    static void Deserialize(std::string json,PDC::Robot** robot) { RobotPersistence::Deserialize(json,robot); }
};
}

class RobotPersistenceTest : public ::testing::Test
{
public:
    std::string jsonParse(std::string json)
    {
        jsonxx::Object object;
        object.parse(json);
        return object.json();
    }

    PDC::Robot* createCompleteRobot()
    {
        PDC::PrismaticLinkType* linkType1 = new PDC::PrismaticLinkType("prismatic1");
        linkType1->SetGeometrySource(PDC::GeometrySource("./prismatic1.3ds","object1"));
        linkType1->SetLength(8.0);
        linkType1->SetJointAngle(0.5);
        linkType1->SetTwist(0.25);
        linkType1->SetRole(PDC::LinkType::LINK);

        PDC::RevoluteLinkType*  linkType2 = new PDC::RevoluteLinkType("revolute1");
        linkType2->SetGeometrySource(PDC::GeometrySource("./revolute1.3ds","robot2"));
        linkType2->SetLength(10.0);
        linkType2->SetOffset(1.0);
        linkType2->SetTwist(0.5);
        linkType2->SetRole(PDC::LinkType::END_EFFECTOR);

        PDC::Robot* robot = new PDC::Robot();
        robot->AppendLink(new PDC::Link(linkType1));
        robot->GetLink(0)->SetJointMove(0.75);
        robot->AppendLink(new PDC::Link(linkType1));
        robot->GetLink(1)->SetJointMove(0.5);
        robot->AppendLink(new PDC::Link(linkType2));
        robot->GetLink(2)->SetJointMove(0.25);

        PDC::Trajectory* trajectory = robot->GetTrajectory();

        PDC::RobotPosition robotPosition1 = PDC::RobotPosition(0.0);
        PDC::LinkPosition linkPosition11 = PDC::LinkPosition(0.0,0.0);
        PDC::LinkPosition linkPosition12 = PDC::LinkPosition(0.5,0.5);
        PDC::LinkPosition linkPosition13 = PDC::LinkPosition(0.75,0.75);
        robotPosition1.AddLinkPosition(linkPosition11);
        robotPosition1.AddLinkPosition(linkPosition12);
        robotPosition1.AddLinkPosition(linkPosition13);
        trajectory->AddRobotPosition(robotPosition1);

        PDC::RobotPosition robotPosition2 = PDC::RobotPosition(1.0);
        PDC::LinkPosition linkPosition21 = PDC::LinkPosition(1.0,1.0);
        PDC::LinkPosition linkPosition22 = PDC::LinkPosition(1.5,1.5);
        PDC::LinkPosition linkPosition23 = PDC::LinkPosition(1.75,1.75);
        robotPosition2.AddLinkPosition(linkPosition21);
        robotPosition2.AddLinkPosition(linkPosition22);
        robotPosition2.AddLinkPosition(linkPosition23);
        trajectory->AddRobotPosition(robotPosition2);

        return robot;
    }

    std::string createCompleteRobotJSON()
    {
        std::string robotJson;
        robotJson.append("{");
        robotJson.append("  \"robot\": {");
        robotJson.append("    \"links\": [ ");
        robotJson.append("         { \"joint_move\": 0.75, \"link_type_id\": \"prismatic1\"  },");
        robotJson.append("         { \"joint_move\": 0.5,  \"link_type_id\": \"prismatic1\"  },");
        robotJson.append("         { \"joint_move\": 0.25, \"link_type_id\": \"revolute1\"  } ");
        robotJson.append("    ]");
        robotJson.append("  }, ");
        robotJson.append("  \"trajectory\": {");
        robotJson.append("    \"robot_positions\": [");
        robotJson.append("        { \"time_instant\": 0.0, \"links_positions\": [ ");
        robotJson.append("                                   { \"joint_position\": 0.0,  \"joint_velocity\": 0.0 },");
        robotJson.append("                                   { \"joint_position\": 0.5,  \"joint_velocity\": 0.5 },");
        robotJson.append("                                   { \"joint_position\": 0.75, \"joint_velocity\": 0.75 }");
        robotJson.append("                                 ] },");
        robotJson.append("        { \"time_instant\": 1.0, \"links_positions\": [ ");
        robotJson.append("                                   { \"joint_position\": 1.0,  \"joint_velocity\": 1.0 },");
        robotJson.append("                                   { \"joint_position\": 1.5,  \"joint_velocity\": 1.5 },");
        robotJson.append("                                   { \"joint_position\": 1.75, \"joint_velocity\": 1.75 }");
        robotJson.append("                                 ] }");
        robotJson.append("    ]");
        robotJson.append("  }");
        robotJson.append("}");
        return robotJson;
    }

    std::string createEmptyRobotJSON()
    {
        std::string expectedJson;
        expectedJson.append("{ ");
        expectedJson.append("  \"robot\": { \"links\": [ ] }, ");
        expectedJson.append("  \"trajectory\": { \"robot_positions\":[] }, ");
        expectedJson.append("}");
        return expectedJson;
    }

};




TEST_F(RobotPersistenceTest,serializeEmptyRobotAsJSON)
{
    PDC::Robot* emptyRobot = new PDC::Robot();
    std::string actualJson;
    DMC::RobotPersistenceExposer::Serialize(emptyRobot,&actualJson);    
    delete emptyRobot;
    std::string expectedJson = createEmptyRobotJSON();
    ASSERT_EQ(jsonParse(expectedJson),jsonParse(actualJson));
}

TEST_F(RobotPersistenceTest,serializeCompleteRobotAsJSON)
{
    PDC::Robot* completeRobot = createCompleteRobot();
    std::string actualJson;
    DMC::RobotPersistenceExposer::Serialize(completeRobot,&actualJson);
    std::string expectedJson = createCompleteRobotJSON();
    ASSERT_STREQ(jsonParse(expectedJson).c_str(),jsonParse(actualJson).c_str());
}

TEST_F(RobotPersistenceTest,deserializeEmptyRobot)
{
    std::string emptyRobotJSON = createEmptyRobotJSON();
    PDC::Robot* robot = NULL;
    DMC::RobotPersistenceExposer::Deserialize(emptyRobotJSON,&robot);
    /*
    PDC::Pose pose;
    robot->GetPose(pose);
    for(unsigned int line=0; line < 4;line++)
    {
        for(unsigned int column=0; column < 4; column++)
        {
            ASSERT_DOUBLE_EQ(0.0, pose[line][column]);
        }
    }
    */
    ASSERT_EQ(0,robot->LinkCount());
    PDC::Trajectory* trajectory = robot->GetTrajectory();
    ASSERT_EQ(0,trajectory->GetRobotPositionCount());
    delete robot;
}

TEST_F(RobotPersistenceTest,deserializeCompleteRobotJSON)
{
    /*
    std::string completeRobotJSON = createCompleteRobotJSON();
    PDC::Robot* robot = NULL;
    DMC::RobotPersistenceExposer::Deserialize(completeRobotJSON,&robot);
    PDC::Pose pose;
    robot->GetPose(pose);
    ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]);
    ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]);
    ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]);
    ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]); ASSERT_DOUBLE_EQ(0.0, pose[0][0]);

    ASSERT_EQ(3,robot->LinkCount());
    ASSERT_DOUBLE_EQ(0.75,robot->GetLink(0)->GetJointMove());
    ASSERT_DOUBLE_EQ(0.5,robot->GetLink(1)->GetJointMove());
    ASSERT_DOUBLE_EQ(0.25,robot->GetLink(2)->GetJointMove());
    ASSERT_STREQ("revolute1",robot->GetLink(0)->GetLinkType()->GetId().c_str());
    ASSERT_STREQ("prismatic1",robot->GetLink(1)->GetLinkType()->GetId().c_str());
    ASSERT_STREQ("prismatic1",robot->GetLink(2)->GetLinkType()->GetId().c_str());

    #TODO
    ASSERT  LinkTypeRepository contains all link types
    */
}



