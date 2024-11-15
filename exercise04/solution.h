// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include "mesh/mesh.h"
#include "mesh/3d.h"


void sphere_with_triangular_faces(
  std::string const& full_path_output_file,
  double radius,
  double center_x, double center_y, double center_z
);