#include <gtest/gtest.h>
#include "Face.h"

PDC::Point makePoint(double x,double y,double z)
{
    PDC::Point point;
    point.x = x;
    point.y = y;
    point.z = z;
    return point;
}

TEST(FaceTest,getParametersShouldReturnPreviouslySetParameters)
{
    PDC::Face face;
    PDC::Point vertex_1 = makePoint(0.0,0.0,0.0);
    PDC::Point vertex_2 = makePoint(100.0,50.0,10.0);
    PDC::Point vertex_3 = makePoint(200.0,300.0,400.0);
    long red = 10;
    long green = 20;
    long blue = 30;
    face.SetParameters(vertex_1,vertex_2,vertex_3,red,green,blue);

    PDC::Point out_vertex_1;
    PDC::Point out_vertex_2;
    PDC::Point out_vertex_3;
    long out_red, out_green, out_blue;
    face.GetParameters(out_vertex_1,out_vertex_2,out_vertex_3,out_red,out_green,out_blue);

    EXPECT_EQ(vertex_1.x,out_vertex_1.x);
    EXPECT_EQ(vertex_1.x,out_vertex_1.x);
    EXPECT_EQ(vertex_1.x,out_vertex_1.x);

    EXPECT_EQ(vertex_2.x,out_vertex_2.x);
    EXPECT_EQ(vertex_2.x,out_vertex_2.x);
    EXPECT_EQ(vertex_2.x,out_vertex_2.x);

    EXPECT_EQ(vertex_3.x,out_vertex_3.x);
    EXPECT_EQ(vertex_3.x,out_vertex_3.x);
    EXPECT_EQ(vertex_3.x,out_vertex_3.x);

    EXPECT_EQ(red,out_red);
    EXPECT_EQ(green,out_green);
    EXPECT_EQ(blue,out_blue);
}
