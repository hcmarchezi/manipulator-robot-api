// Robot.cpp: implementation of the Robot class.
//
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif

#include "Robot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::Robot::Robot()
{
    _trajectory = new PDC::Trajectory();
    PDC::PoseFunctions::zeros(_pose);
}

PDC::Robot::~Robot()
{
    for (unsigned int i = 0;i < _links.size();i++)
    {
        delete _links[i];
    }
    delete _trajectory;
}

void PDC::Robot::AppendLink(PDC::Link * newLink)
{
    _links.push_back(newLink);
}

void PDC::Robot::InsertLink(unsigned int index,PDC::Link* newLink)
{
    std::vector<Link*>::iterator it = _links.begin();
    for(unsigned int times=0; times < index; times++) it++;
    _links.insert(it,newLink);

}

void PDC::Robot::RemoveLink(unsigned int index)
{
    std::vector<Link*>::iterator it = _links.begin();
    for(unsigned int times=0; times < index; times++) it++;
    _links.erase(it);
}

PDC::Link* PDC::Robot::GetLink(unsigned int index)
{
    return _links[index];
}

unsigned int PDC::Robot::LinkCount()
{
    return _links.size();
}

void PDC::Robot::SetPose(PDC::Pose& pose)
{
    PDC::PoseFunctions::copy(pose,_pose);
}

void PDC::Robot::GetPose(PDC::Pose& pose)
{
    PDC::PoseFunctions::copy(_pose,pose);
}

PDC::Trajectory* PDC::Robot::GetTrajectory()
{
    return _trajectory;
}
