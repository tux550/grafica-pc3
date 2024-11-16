#include "solution.h"
#include <set>
#include <map>

void painter_algorithm_simple_cosine_illumination(
std::string const& full_path_input_mesh,
std::string const& full_path_output_image,
double min_x_coordinate_in_projection_plane,
double min_y_coordinate_in_projection_plane,
double max_x_coordinate_in_projection_plane,
double max_y_coordinate_in_projection_plane,
size_t width_in_pixels,
size_t height_in_pixels) {
  // Load the mesh
  mesh::Mesh mesh(full_path_input_mesh);

  // Create projection plane
  mesh::ProjectionPlane projection_plane(
    min_x_coordinate_in_projection_plane,
    min_y_coordinate_in_projection_plane,
    max_x_coordinate_in_projection_plane,
    max_y_coordinate_in_projection_plane,
    width_in_pixels,
    height_in_pixels);
  // Define vision vector
  mesh::Vertex3D light_direction(0, 0, 1);
  // Triangle list
  std::vector<std::tuple<mesh::Face2D, int, double>> triangles_ilumination_distance;

  // For each face in the mesh project it to the projection plane
  for (mesh::Face3D & face : mesh.get_faces()) {
    std::optional<mesh::Face2D> face2d = projection_plane.project(face);
    if (face2d.has_value()) {
      // Get distance from the origin
      double distance = projection_plane.distance(face);
      // Calculate the cosine of the angle between the face normal and the vision vector
      double cosine = -dot_product(face.get_normal().normalized(), light_direction);
      // If negative, skip the face
      if (cosine < 0) {
        continue;
      }
      // Calculate the illumination
      double illumination = cosine * 255;
      // Round up the illumination
      int illumination_rounded = static_cast<int>(std::ceil(illumination));
      
      // Add the face to the list
      triangles_ilumination_distance.push_back(std::make_tuple(face2d.value(), illumination_rounded, distance));
    }
  }

  // Sort the triangles by distance
  std::sort(triangles_ilumination_distance.begin(), triangles_ilumination_distance.end(), [](auto & a, auto & b) {
    return std::get<1>(a) < std::get<1>(b);
  });

  // Draw the triangles
  for (auto & [face, illumination, dist] : triangles_ilumination_distance) {
    for (size_t i = 0; i < face.vertices.size(); i++) {
      projection_plane.draw_triangle(face,  illumination);
    }
  }

  // Save the image
  projection_plane.save_png(full_path_output_image);
}