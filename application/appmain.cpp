#include "appmain.h"

#include "robotpersistence.h"
#include "geometryreader.h"
#include "linktyperepository.h"
#include "linktypepersistence.h"

namespace TMC {

AppMain::AppMain():_robot(new PDC::Robot())
{
}

AppMain::~AppMain()
{
    deleteRobot();
}


void AppMain::loadLinkTypeList(const std::vector<std::string>& linktypeFilePaths)
{
    DMC::GeometryReader reader;
    for(unsigned int index=0; index < linktypeFilePaths.size(); index++)
    {
        PDC::LinkType* linkType = DMC::LinkTypePersistence::LoadFromFile(linktypeFilePaths[index]);
        PDC::GeometrySource geometrySource = linkType->GetGeometrySource();
        PDC::Geometry* geometry = reader.read3DSFile(geometrySource);
        linkType->SetGeometry(geometry);
        PDC::LinkTypeRepository::Add(linkType);
    }
}

///////////// user actions //////////////////

void AppMain::newRobot()
{
    deleteRobot();
    _robot = new PDC::Robot();
}

void AppMain::loadRobot(const std::string& filename)
{
    deleteRobot();    
    _robot = DMC::RobotPersistence::Load(filename);
    _robotFilename = filename;
}

void AppMain::saveRobot(const std::string& filename)
{
    if (_robot == NULL) return;
    DMC::RobotPersistence::Save(_robot, filename);
    _robotFilename = filename;
}

////////////////////////////////////////////////////




void AppMain::deleteRobot()
{
    if (_robot != NULL)
    {
        delete _robot;
        _robot = NULL;
    }
}



PDC::Robot* AppMain::robot()
{
    return _robot;
}

const std::string& AppMain::robotFilename()
{
    return _robotFilename;
}

} // namespace TMC
