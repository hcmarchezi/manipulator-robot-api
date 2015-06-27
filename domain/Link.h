// Link.h: interface for the Link class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LINK_H
#define LINK_H

#include "LinkType.h"

namespace PDC
{

class Link
{
public:
    Link();
    Link(PDC::LinkType* linkType);
    virtual ~Link();
    void SetJointMove(double jointMove);
    double GetJointMove();
    void SetLinkType(PDC::LinkType* linkType);
    PDC::LinkType* GetLinkType();

protected:
    double _jointMove;
    PDC::LinkType* _linkType;
};

}

#endif
