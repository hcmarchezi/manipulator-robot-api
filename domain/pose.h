#ifndef POSE_H
#define POSE_H

#include<vector>

namespace PDC
{
    typedef double Pose[4][4];
    class PoseFunctions
    {
    public:
        static void copy(Pose& origin,Pose& destination);
        static bool equal(Pose& pose1,Pose& pose2);
        static void zeros(Pose& pose);
        static void identity(Pose& pose);
    };
}

#endif // POSE_H
