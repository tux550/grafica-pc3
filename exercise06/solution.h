// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include "mesh/mesh.h"
#include "mesh/3d.h"

void rotate_mesh_around_line(
    const std::string& full_path_input_mesh,
    mesh::Line3D axis_of_rotation,
    double alpha, // Degrees to rotate
    const std::string& full_path_output_mesh
);