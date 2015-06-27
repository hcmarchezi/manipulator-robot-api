#ifndef CONCRETELINKTYPE_H
#define CONCRETELINKTYPE_H

#include "LinkType.h"

class ConcreteLinkType : public PDC::LinkType
{
public:
    ConcreteLinkType(std::string id):LinkType(id) { }
    void CalculateFrame(double variableparam,double (* frame)[4][4])
    {
    }
    std::string GetJointType()
    {
        return "concrete";
    }
};

#endif // CONCRETELINKTYPE_H
