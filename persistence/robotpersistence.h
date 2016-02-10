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
    static void Save(PDC::Robot* robot, const std::string& filename);
    static PDC::Robot* Load(const std::string& filename);
    static void Remove(const std::string& filename);

protected:
    static void Serialize(PDC::Robot* robot, std::string *robotJson);
    static void Deserialize(const std::string& json,PDC::Robot** robot);
};
}

#endif // ROBOTPERSISTENCE_H
