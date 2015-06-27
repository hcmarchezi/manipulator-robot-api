// Robot.h: interface for the Robot class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ROBOT_H
#define ROBOT_H

#include "Link.h"
#include "pose.h"
#include "trajectory.h"
#include "graphicobject.h"

#include <vector>

namespace PDC
{
    class Robot : public GraphicObject
    {      
    public:
        Robot();
        virtual ~Robot();
        void InsertLink(unsigned int index,PDC::Link* newLink);
        void AppendLink(PDC::Link * newlink);
        void RemoveLink(unsigned int index);
        PDC::Link* GetLink(unsigned int index);
        unsigned int LinkCount();

        void SetPose(PDC::Pose& pose);
        void GetPose(PDC::Pose& pose);

        PDC::Trajectory* GetTrajectory();

    protected:
        std::vector<Link *> _links;
        PDC::Pose _pose;
        PDC::Trajectory* _trajectory;
    };
}

#endif
