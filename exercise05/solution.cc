#include "solution.h"

void sphere_with_texture(
    const std::string& full_path_input_ply,
    const std::string& full_path_texture,
    const std::tuple<double, double, double>& center,
    const std::string& full_path_output_ply
) {
  // Load the input mesh
  mesh::Mesh mesh(full_path_input_ply);
  // Set the texture file
  mesh.set_texture_file(full_path_texture);
  // For each vertex get the spherical coordinates
  for (auto& vertex : mesh.get_vertices()) {
    // Get the spherical coordinates
    double x = vertex.x - std::get<0>(center);
    double y = vertex.y - std::get<1>(center);
    double z = vertex.z - std::get<2>(center);
    double r = std::sqrt(x * x + y * y + z * z);
    double theta = std::acos(z / r);
    double phi = std::atan2(y, x);
    // Get the texture coordinates
    double u = (phi+M_PI) / (2 * M_PI); // +M_PI to avoid negative values
    double v = (M_PI-theta) / M_PI;
    // Set the texture coordinates
    vertex.u = u;
    vertex.v = v;
  }
  // Save the mesh
  mesh.save_ply(full_path_output_ply.c_str(), true);
}