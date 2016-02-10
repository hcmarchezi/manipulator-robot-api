// LinkType.cpp: implementation of the LinkType class.
//
//////////////////////////////////////////////////////////////////////

#include "LinkType.h"

#include "matrix.h"

PDC::LinkType::LinkType(std::string id):_geometrySource("","")
{
    _id = id;
    _role = PDC::LinkType::UNKNOWN;
    _geometry = NULL;
    PDC::Matrix::SetIdentity(&_geometryPose);
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

void PDC::LinkType::SetGeometryPose(double matrix[4][4])
{
    _geometryPose[0][0] = matrix[0][0];
    _geometryPose[0][1] = matrix[0][1];
    _geometryPose[0][2] = matrix[0][2];
    _geometryPose[0][3] = matrix[0][3];

    _geometryPose[1][0] = matrix[1][0];
    _geometryPose[1][1] = matrix[1][1];
    _geometryPose[1][2] = matrix[1][2];
    _geometryPose[1][3] = matrix[1][3];

    _geometryPose[2][0] = matrix[2][0];
    _geometryPose[2][1] = matrix[2][1];
    _geometryPose[2][2] = matrix[2][2];
    _geometryPose[2][3] = matrix[2][3];

    _geometryPose[3][0] = matrix[3][0];
    _geometryPose[3][1] = matrix[3][1];
    _geometryPose[3][2] = matrix[3][2];
    _geometryPose[3][3] = matrix[3][3];
}

void PDC::LinkType::GetGeometryPose(double (* matrix)[4][4]) const
{
    (*matrix)[0][0] = _geometryPose[0][0];
    (*matrix)[0][1] = _geometryPose[0][1];
    (*matrix)[0][2] = _geometryPose[0][2];
    (*matrix)[0][3] = _geometryPose[0][3];

    (*matrix)[1][0] = _geometryPose[1][0];
    (*matrix)[1][1] = _geometryPose[1][1];
    (*matrix)[1][2] = _geometryPose[1][2];
    (*matrix)[1][3] = _geometryPose[1][3];

    (*matrix)[2][0] = _geometryPose[2][0];
    (*matrix)[2][1] = _geometryPose[2][1];
    (*matrix)[2][2] = _geometryPose[2][2];
    (*matrix)[2][3] = _geometryPose[2][3];

    (*matrix)[3][0] = _geometryPose[3][0];
    (*matrix)[3][1] = _geometryPose[3][1];
    (*matrix)[3][2] = _geometryPose[3][2];
    (*matrix)[3][3] = _geometryPose[3][3];
}
