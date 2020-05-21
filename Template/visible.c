
//----------------------------------------------------------
#include <stdio.h>

#include "visible.h"

//----------------------------------------------------------
int isVisible( Vertex *cameraPosition, Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO:  Purpose:  Determine if the triangle represented by
  //          vertices v1, v2, and v3 is visible from the given
  //          camera position.
  //
  //        Compute the toTriangle vector from the camera position
  //          to v1 of the triangle.
  //
  //        Derive the surface normal for the triangle by
  //          computing the cross product of the vector from v1
  //          to v2 with the vector from v1 to v3.
  //
  //        Compute the angle between the toTriangle vector and
  //          the surface normal vector.
  //
  //        Return 1 if this angle indicates the triangle is
  //          visible from the camera position, 0 otherwise.
    // 21 lines of code
    
    Vertex toTriangle;
    Vertex normal;
    Vertex a;
    Vertex b;
    
    a.x = v2->x - v1->x;
    a.y = v2->y - v1->y;
    a.z = v2->z - v1->z;
    
    b.x = v3->x - v1->x;
    b.y = v3->y - v1->y;
    b.z = v3->z - v1->z;
    
    normal.x = a.y * b.z - a.z * b.y;
    normal.y = a.z * b.x - a.x * b.z;
    normal.z = a.x * b.y - a.y * b.x;
    
    toTriangle.x = v1->x - cameraPosition->x;
    toTriangle.y = v1->y - cameraPosition->y;
    toTriangle.z = v1->z - cameraPosition->z;
    
    if( (normal.x * toTriangle.x + normal.y * toTriangle.y + normal.z * toTriangle.z) < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//----------------------------------------------------------
