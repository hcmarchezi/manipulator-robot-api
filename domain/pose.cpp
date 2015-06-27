#include "pose.h"

void PDC::PoseFunctions::copy(Pose& origin,Pose& destination)
{
    for (unsigned int line=0; line < 4; line++)
    {
        for(unsigned int column=0; column < 4; column++)
        {
            destination[line][column] =  origin[line][column];
        }
    }
}


bool PDC::PoseFunctions::equal(Pose& pose1,Pose& pose2)
{
    for(unsigned int line=0; line < 4;line++)
    {
        for(unsigned int column=0; column < 4; column++)
        {
            if (pose1[line][column] != pose2[line][column])
            {
                return false;
            }
        }
    }
    return true;
}


void PDC::PoseFunctions::zeros(Pose& pose)
{
    for(unsigned int line=0; line < 4;line++)
    {
        for(unsigned int column=0; column < 4; column++)
        {
            pose[line][column] = 0.0;
        }
    }
}

void PDC::PoseFunctions::identity(Pose& pose)
{
    for(unsigned int line=0; line < 4;line++)
    {
        for(unsigned int column=0; column < 4; column++)
        {
            if (line == column)
                pose[line][column] = 1.0;
            else
                pose[line][column] = 0.0;
        }
    }
}
