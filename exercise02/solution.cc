#include "solution.h"

void cube_with_triangular_faces(
  double min_x, double max_x,
  double min_y, double max_y,
  double min_z, double max_z,
  std::string filename
) {
  mesh::Mesh mesh = mesh::cuboidTriangularFaces(
    min_x, max_x,
    min_y, max_y,
    min_z, max_z
  );
  mesh.save_ply(filename.c_str());
}