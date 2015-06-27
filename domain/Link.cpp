// Link.cpp: implementation of the Link class.
//
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif

#include "Link.h"
#include <GL/glu.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PDC::Link::Link()
{
    _jointMove = 0.0;
    _linkType  = NULL;
}

PDC::Link::Link(PDC::LinkType* linkType)
{
    _jointMove = 0.0;
    _linkType = linkType;
}

PDC::Link::~Link()
{
}

void PDC::Link::SetJointMove(double jointMove)
{
    _jointMove = jointMove;
}

double PDC::Link::GetJointMove()
{
    return _jointMove;
}

void PDC::Link::SetLinkType(PDC::LinkType* linkType)
{
    _linkType = linkType;
}

PDC::LinkType* PDC::Link::GetLinkType()
{
    return _linkType;
}

