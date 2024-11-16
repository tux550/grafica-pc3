// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include "mesh/mesh.h"
#include "mesh/3d.h"

void translate_mesh(
    const std::string& full_path_input_mesh,
    mesh::Vertex3D displacement,
    const std::string& full_path_output_mesh
);