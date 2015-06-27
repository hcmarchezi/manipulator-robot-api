#ifndef ROBOTPERSISTENCE_H
#define ROBOTPERSISTENCE_H

#include <string>
#include "Robot.h"
#include "jsonxx.h"

namespace DMC
{
class RobotPersistence
{
public:
    static void Save(PDC::Robot* robot) { }
    static PDC::Robot* Load(std::string robotId) { return NULL; }
    static void Remove(PDC::Robot* robot) { }

protected:
    static void Serialize(PDC::Robot* robot, std::string *robotJson);
    static void Deserialize(std::string json,PDC::Robot** robot);
};
}

#endif // ROBOTPERSISTENCE_H
