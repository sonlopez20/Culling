
//----------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "projection.h"
#include "triangle.h"
#include "vertex.h"
#include "view.h"
#include "visible.h"

//----------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s <modelFileName> <viewFileName>\n", argv[0] );
    exit( 1 );
  }

  //--------------------------------------
  // Load the desired model and view.
  Model *m = loadModel( argv[1] );
  View *v = loadView( argv[2] );

  // Compute the projection corresponding to the view.
  Projection *p = computeProjection( v );

  //--------------------------------------
  // Dump all of these data structures as a check.
  dumpModel( m );
  dumpView( v );
  dumpProjection( p );

  //--------------------------------------
  // Allocate a place for the projected versions of the vertices
  // to go.

  // TODO: Allocate enough space for the number of vertices the
  //       model has.  This will be the space for the projected
  //       versions of the vertices.  (Remember to check if the
  //       space got allocated OK!)

    //6 lines of code.
    Vertex* vertex;
    int numVertices = m->m_numVertices;
    if (numVertices > 0)
    {
        vertex = (Vertex *) calloc( numVertices, sizeof( Vertex ) );
        if ( vertex == NULL )
        {
          fprintf( stderr, "main: Unable to allocate %d Vert%s.\n",
            numVertices, (numVertices == 1) ? "ex" : "ices" );
        }
    }
    
  // And now project the vertices into that space ...

  // TODO: Project the vertices of the model into the space you
  //       just allocated using projectVertexList2().
    // 1 line of code
    projectVertexList2(p,m->m_vertex, numVertices, vertex);

  //--------------------------------------
  // Print the canvas size for the SDF file.
  printf( "c %4d %4d\n", v->m_width, v->m_height );

  //--------------------------------------
  // Draw lines corresponding to the viewport region.

  // TODO: Print four 'l' lines, corresponding to the
  //         the edges of the viewport region.
  //       Start in the lower-left corner (xMin, yMin) and draw
  //         the lines going counter-clockwise.
    //8 lines of code
    
    printf("l%7.1d%9.1d%9.1d%9.1d\n",
    v->m_portalXMin, v->m_portalYMin, v->m_portalXMax, v->m_portalYMin);
    
    printf("l%7.1d%9.1d%9.1d%9.1d\n",
    v->m_portalXMax, v->m_portalYMin, v->m_portalXMax, v->m_portalYMax);
    
    printf("l%7.1d%9.1d%9.1d%9.1d\n",
    v->m_portalXMax, v->m_portalYMax, v->m_portalXMin, v->m_portalYMax);
    
    printf("l%7.1d%9.1d%9.1d%9.1d\n",
    v->m_portalXMin, v->m_portalYMax, v->m_portalXMin, v->m_portalYMin);

  //--------------------------------------
  // Construct a Vertex representing the camera position.
  // Remember, if the camera distance is 0.0 (representing a
  // PARALLEL projection), it should be thought of as being
  // very far away.

  // TODO: Construct a Vertex holding the worldspace position of
  //       the camera.  If the projection is PARALLEL, remember
  //       that the camera's z coordinate should be at effectively
  //       "infinity".
    // 2 lines of code
    Vertex cameraPosition;
    cameraPosition.x = 0;
    cameraPosition.y = 0;
    cameraPosition.z = p->m_cameraDistance;
    if (cameraPosition.z == 0)
    {
        cameraPosition.z = +HUGE_VAL;
    }

  //--------------------------------------
  // Consider each of the faces of the model.  If the face is
  // not visible (that is, does not face the camera position),
  // ignore it.  If the face is visible, dump its triangle.
  //
  // Check for visibility using the isVisible() function and the
  // ORIGINAL vertex positions, the ones in m->m_vertex.  These
  // are still in worldspace.
  //
  // Dump the triangle using the enhanced dumpTriangle() function
  // and the PROJECTED vertex positions.  These are in screen
  // space.

  // TODO: For each face of the model, draw the triangle
  //       represented by its three vertices using the enhanced
  //       version of dumpTriangle().  Draw the triangle ONLY IF
  //       the triangle is visible (use isVisible() to determine
  //       this).
    //14 lines of code
    int j;
    for(j = 0; j < m->m_numFaces; j++)
    {
        Vertex v4,v5,v6;
        int result = isVisible(&cameraPosition,
                    &m->m_vertex[m->m_face[j].v1],
                    &m->m_vertex[m->m_face[j].v2],
                    &m->m_vertex[m->m_face[j].v3]);
        if (result == 1)
        {
            projectVertex(p,&m->m_vertex[m->m_face[j].v1],&v4);
            projectVertex(p,&m->m_vertex[m->m_face[j].v2],&v5);
            projectVertex(p,&m->m_vertex[m->m_face[j].v3],&v6);
            
            dumpTriangle(v,&v4,&v5,&v6);
        }
    }
    

  //--------------------------------------
  // Free all of our allocated resources ...

  // TODO: Free all allocated structures.

  // ... and exit with no error.
    //4 lines of code
    freeView (v);
    freeModel (m);
    freeProjection (p);
    free (vertex);

  // TODO: Return from main indicating no error.
    // 1 line of code
    return 0;
}

//----------------------------------------------------------

