// PrismaticLinkType.h: interface for the PrismaticLinkType class.
//
//////////////////////////////////////////////////////////////////////

#ifndef PRISMATICLINKTYPE_H
#define PRISMATICLINKTYPE_H

#include "LinkType.h"

namespace PDC
{

class PrismaticLinkType : public LinkType
{
public:	
    PrismaticLinkType(std::string id);
    virtual ~PrismaticLinkType();

	void SetJointAngle(double angle);
	double GetJointAngle();

    void CalculateFrame(double jointMove,double (* frame)[4][4]);
    std::string GetJointType();

private:
    double _jointAngle;
};

}

#endif
