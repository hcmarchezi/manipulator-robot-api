#ifndef TMC_APPMAIN_H
#define TMC_APPMAIN_H

#include "Robot.h"

namespace TMC {

class AppMain
{
public:
    AppMain();
    ~AppMain();

    // app initialization
    void loadLinkTypeList(const std::vector<std::string>& linktypeFilePaths);

    // user actions
    void newRobot();
    void loadRobot(const std::string& filename);
    void saveRobot(const std::string& filename);

    PDC::Robot* robot();
    const std::string& robotFilename();    

protected:
    void deleteRobot();

    PDC::Robot* _robot;
    std::string _robotFilename;

};

} // namespace TMC

#endif // TMC_APPMAIN_H
