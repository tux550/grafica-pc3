#include "solution.h"

void rotate_mesh_around_line(
    const std::string& full_path_input_mesh,
    mesh::Line3D axis_of_rotation,
    double alpha, // Degrees to rotate
    const std::string& full_path_output_mesh
) {
  // Load the input mesh
  mesh::Mesh mesh(full_path_input_mesh);
  // Convert alpha to radians
  auto alpha_rads = alpha * M_PI / 180;
  // For each vertex get the spherical coordinates
  for (auto& vertex : mesh.get_vertices()) {
    // Rotate vertex around axis_of_rotation
    vertex = mesh::rotate_vertex(vertex, axis_of_rotation, alpha_rads);
  }
  // Save the mesh in same format as input
  mesh.save(full_path_output_mesh.c_str());
}