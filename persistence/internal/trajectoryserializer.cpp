#include "trajectoryserializer.h"

namespace DMC {
namespace Internal {

jsonxx::Object* TrajectorySerializer::serialize(PDC::Trajectory* trajectory)
{
    jsonxx::Object* jsonTrajectory = new jsonxx::Object();
    jsonxx::Array jsonRobotPositions;
    for (int i=0; i < trajectory->GetRobotPositionCount(); i++)
    {
        jsonxx::Object jsonRobotPosition;
        PDC::RobotPosition robotPosition = trajectory->GetRobotPosition(i);
        jsonRobotPosition << "time_instant" << robotPosition.GetInstantTime();
        jsonxx::Array jsonLinksPositions;
        for (int j=0; j < robotPosition.GetLinkPositionsSize(); j++)
        {
            jsonxx::Object jsonLinkPosition;
            PDC::LinkPosition linkPosition = robotPosition.GetLinkPosition(j);
            jsonLinkPosition << "position" << linkPosition.GetJointPosition();
            jsonLinkPosition << "velocity" << linkPosition.GetJointVelocity();
            jsonLinksPositions << jsonLinkPosition;
        }
        jsonRobotPosition << "links_positions" << jsonLinksPositions;
        jsonRobotPositions << jsonRobotPosition;
    }
    (*jsonTrajectory) << "robot_positions" << jsonRobotPositions;
    return jsonTrajectory;
}

PDC::Trajectory* TrajectorySerializer::deserialize(jsonxx::Object& json)
{
    PDC::Trajectory* trajectory = new PDC::Trajectory();
    jsonxx::Array  jsonRobotPositions = json.get<jsonxx::Array>("robot_positions");
    for (size_t i=0; i < jsonRobotPositions.size(); i++)
    {
        jsonxx::Object jsonRobotPosition = jsonRobotPositions.get<jsonxx::Object>(i);
        double instantTime = jsonRobotPosition.get<jsonxx::Number>("time_instant");
        PDC::RobotPosition robotPosition = PDC::RobotPosition(instantTime);
        jsonxx::Array jsonLinksPositions = jsonRobotPosition.get<jsonxx::Array>("links_positions");
        for (size_t j=0; j < jsonLinksPositions.size(); j++)
        {
            jsonxx::Object jsonLinkPosition = jsonLinksPositions.get<jsonxx::Object>(j);
            double position = jsonLinkPosition.get<jsonxx::Number>("position");
            double velocity = jsonLinkPosition.get<jsonxx::Number>("velocity");
            PDC::LinkPosition linkPosition = PDC::LinkPosition(position,velocity);
            robotPosition.AddLinkPosition(linkPosition);
        }
        trajectory->AddRobotPosition(robotPosition);
    }
    return trajectory;
}

} // namespace Internal
} // namespace DMC
