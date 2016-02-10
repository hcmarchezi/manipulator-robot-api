#include "robotpersistence.h"

#include "jsonxx.h"
#include "RevoluteLinkType.h"
#include "PrismaticLinkType.h"
#include "linktyperepository.h"

#include <fstream>
#include <cstdio>

namespace DMC
{
    void RobotPersistence::Save(PDC::Robot* robot, const std::string& filename)
    {
        std::string json;
        Serialize(robot,&json);
        std::ofstream file(filename.c_str());
        file << json;
        file.close();
    }

    PDC::Robot* RobotPersistence::Load(const std::string& filename)
    {
        std::ifstream file(filename.c_str());
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        std::string json = buffer.str();

        PDC::Robot* robot;
        Deserialize(json,&robot);
        return robot;
    }

    void RobotPersistence::Remove(const std::string& filename)
    {
        std::remove(filename.c_str());
    }

    void RobotPersistence::Serialize(PDC::Robot* robot,std::string* robotJson)
    {
        jsonxx::Object root;
        jsonxx::Object robotField;
        jsonxx::Object linkType;

        jsonxx::Array links;
        for(unsigned int index=0; index < robot->LinkCount(); index++)
        {
            jsonxx::Object link;
            link << "joint_move" << robot->GetLink(index)->GetJointMove();
            link << "link_type_id" << robot->GetLink(index)->GetLinkType()->GetId();
            links << link;
        }
        robotField << "links" << links;
        root << "robot" << robotField;

        PDC::Trajectory* trajectory = robot->GetTrajectory();
        jsonxx::Object trajectoryField;
        jsonxx::Array robotPositionsField;
        for(unsigned int index=0; index < trajectory->GetRobotPositionCount(); index++)
        {
            jsonxx::Object robotPositionField;
            PDC::RobotPosition robotPosition = trajectory->GetRobotPosition(index);
            robotPositionField << "time_instant" << robotPosition.GetInstantTime();
            jsonxx::Array linksPositionsField;
            for (unsigned int linkNumber=0; linkNumber < robotPosition.GetLinkPositionsSize(); linkNumber++)
            {
                jsonxx::Object linkPositionField;
                PDC::LinkPosition linkPosition = robotPosition.GetLinkPosition(linkNumber);
                linkPositionField << "joint_position" << linkPosition.GetJointPosition();
                linkPositionField << "joint_velocity" << linkPosition.GetJointVelocity();
                linksPositionsField << linkPositionField;
            }
            robotPositionField << "links_positions" << linksPositionsField;
            robotPositionsField << robotPositionField;
        }
        trajectoryField << "robot_positions" << robotPositionsField;
        root << "trajectory" << trajectoryField;

        *robotJson = root.json();
    }

    void RobotPersistence::Deserialize(const std::string &json, PDC::Robot **robot)
    {
        jsonxx::Object jsonWorld = jsonxx::Object();
        jsonWorld.parse(json);
        jsonxx::Object jsonRobot = jsonWorld.get<jsonxx::Object>("robot");

        PDC::Robot* loadedRobot = new PDC::Robot();
        jsonxx::Array jsonLinks = jsonRobot.get<jsonxx::Array>("links");
        for(unsigned int index=0; index < jsonLinks.size(); index++)
        {
            jsonxx::Object jsonLink = jsonLinks.get<jsonxx::Object>(index);
            std::string linkTypeId = jsonLink.get<jsonxx::String>("link_type_id");

            PDC::LinkType* linkType = PDC::LinkTypeRepository::Get(linkTypeId);

            PDC::Link* link = new PDC::Link(linkType);
            double jointMove = jsonLink.get<jsonxx::Number>("joint_move");
            link->SetJointMove(jointMove);
            loadedRobot->AppendLink(link);
        }

        *robot = loadedRobot;
    }
}
