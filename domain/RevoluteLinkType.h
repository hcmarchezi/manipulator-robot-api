// RevoluteLinkType.h: interface for the RevoluteLinkType class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REVOLUTELINKTYPE_H
#define REVOLUTELINKTYPE_H

#include "LinkType.h"

namespace PDC
{

class RevoluteLinkType : public LinkType
{
public:
    RevoluteLinkType(std::string id);
	virtual ~RevoluteLinkType();

    void SetOffset(double offset);
    double GetOffset();

    void CalculateFrame (double jointMove,double (* frame)[4][4]);
    std::string GetJointType();

private:
    double _offset;
};

}

#endif

