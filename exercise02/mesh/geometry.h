#include <cmath>
#include "mesh.h"


#ifndef MESH_BASIC_GEOMETRY_H
#define MESH_BASIC_GEOMETRY_H

namespace mesh {
  // Unit circle meshes
  Mesh unitCircleCube();
  Mesh unitCircleTetrahedron();
  // Base meshes
  Mesh cuboidSquaredFaces(
    double min_x, double max_x,
    double min_y, double max_y,
    double min_z, double max_z
  );
  Mesh cuboidTriangularFaces(
    double min_x, double max_x,
    double min_y, double max_y,
    double min_z, double max_z
  );
}
#endif