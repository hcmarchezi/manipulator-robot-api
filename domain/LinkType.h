// LinkType.h: interface for the LinkType class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LINKTYPE_H
#define LINKTYPE_H

#include "geometry.h"
#include "geometrysource.h"
#include "graphicobject.h"

#include<string>

namespace PDC
{

class LinkType : public GraphicObject
{
public:
    enum Role { BASE, LINK, END_EFFECTOR, UNKNOWN };

public:
    LinkType(std::string id);
    virtual ~LinkType();
    void SetTwist(double twist);
    void SetLength(double length);
    double GetTwist();
    double GetLength();
    std::string GetId();
    void SetRole(PDC::LinkType::Role role);
    std::string GetRole();
    void SetGeometrySource(PDC::GeometrySource geometrySource);
    PDC::GeometrySource GetGeometrySource();
    void SetGeometry(PDC::Geometry* geometry);
    PDC::Geometry* GetGeometry();
    virtual void CalculateFrame(double jointMove,double (* frame)[4][4]) = 0;
    virtual std::string GetJointType() = 0;

protected:
    std::string _id;
    double _twist;
    double _length;
    std::string _role;
    PDC::GeometrySource _geometrySource;
    PDC::Geometry* _geometry;
};

}

#endif
