#include "geometryreader.h"

#include <lib3ds/file.h>
#include <lib3ds/mesh.h>

namespace DMC {

GeometryReader::GeometryReader()
{
}

PDC::Geometry* GeometryReader::read3DSFile(PDC::GeometrySource geometrySource)
{
    std::string fileName = geometrySource.GetFilePath();
    std::string objectName = geometrySource.GetObjectName();

    PDC::Geometry* geometry = new PDC::Geometry();

    Lib3dsFile* file = lib3ds_file_load(fileName.c_str());
    if (!file)
    {
        return geometry;
    }

    Lib3dsMesh * mesh;
    // Search for mesh with given name
    for(mesh = file->meshes;mesh != NULL;mesh = mesh->next)
    {
        if (objectName == mesh->name)
        {
            // Get mesh faces
            for(unsigned int faceIndex = 0; faceIndex < mesh->faces;faceIndex++)
            {
                Lib3dsFace * meshFace = &mesh->faceL[faceIndex];
                Lib3dsPoint* v1 = &mesh->pointL[meshFace->points[0]];
                Lib3dsPoint* v2 = &mesh->pointL[meshFace->points[1]];
                Lib3dsPoint* v3 = &mesh->pointL[meshFace->points[2]];

                PDC::Face face;
                PDC::Point p1 = PDC::Point(v1->pos[0],v1->pos[1],v1->pos[2]);
                PDC::Point p2 = PDC::Point(v2->pos[0],v2->pos[1],v2->pos[2]);
                PDC::Point p3 = PDC::Point(v3->pos[0],v3->pos[1],v3->pos[2]);

                face.SetParameters(p1,p2,p3,255,255,255);
                geometry->AddFace(face);
            }
        }
    }

    lib3ds_file_free(file);

    return geometry;
}



} // namespace DMC
