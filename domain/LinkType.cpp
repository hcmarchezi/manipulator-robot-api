// LinkType.cpp: implementation of the LinkType class.
//
//////////////////////////////////////////////////////////////////////

#include "LinkType.h"

PDC::LinkType::LinkType(std::string id):_geometrySource("","")
{
    _id = id;
    _role = PDC::LinkType::UNKNOWN;
    _geometry = NULL;
}

PDC::LinkType::~LinkType()
{
}

void PDC::LinkType::SetTwist(double twist)
{
    _twist = twist;
}

void PDC::LinkType::SetLength(double length)
{
    _length = length;
}

double PDC::LinkType::GetTwist()
{
    return _twist;
}

double PDC::LinkType::GetLength()
{
    return _length;
}

std::string PDC::LinkType::GetId()
{
    return _id;
}

void PDC::LinkType::SetRole(PDC::LinkType::Role role)
{
    switch (role)
    {
    case PDC::LinkType::BASE:
        _role = "base";
        break;
    case PDC::LinkType::LINK:
        _role = "link";
        break;
    case PDC::LinkType::END_EFFECTOR:
        _role = "end effector";
        break;
    }
}

std::string PDC::LinkType::GetRole()
{
    return _role;
}

void PDC::LinkType::SetGeometrySource(GeometrySource geometrySource)
{
    _geometrySource = geometrySource;
}

PDC::GeometrySource PDC::LinkType::GetGeometrySource()
{
    return _geometrySource;
}

void PDC::LinkType::SetGeometry(PDC::Geometry* geometry)
{
    _geometry = geometry;
}

PDC::Geometry* PDC::LinkType::GetGeometry()
{
    return _geometry;
}
