#include "solution.h"

void translate_mesh(
    const std::string& full_path_input_mesh,
    mesh::Vertex3D displacement,
    const std::string& full_path_output_mesh
) {
  // Load the input mesh
  mesh::Mesh mesh(full_path_input_mesh);
  // Move all vertices
  mesh.displace(displacement);
  // Save the mesh in same format as input
  mesh.save(full_path_output_mesh.c_str());
}