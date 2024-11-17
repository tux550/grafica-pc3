#include "solution.h"
#include <set>
#include <map>

void frames_of_a_textured_sphere_rotating(
std::string const& full_path_input_mesh,
std::string const& full_path_input_texture,
double rotation_line_point_x,
double rotation_line_point_y,
double rotation_line_point_z,
double rotation_line_direction_x,
double rotation_line_direction_y,
double rotation_line_direction_z,
std::string const& filename_without_suffix_output_frames) {
  // Load the mesh
  mesh::Mesh mesh(full_path_input_mesh);

  // Init line
  mesh::Line3D rotation_line(
    // Point
    mesh::Vertex3D(rotation_line_point_x, rotation_line_point_y, rotation_line_point_z),
    // Direction
    mesh::Vertex3D(rotation_line_direction_x, rotation_line_direction_y, rotation_line_direction_z)
  );

  // Load matrix texture using opencv
  cv::Mat texture_image = cv::imread(full_path_input_texture, cv::IMREAD_COLOR);

  // Constants
  const size_t number_of_frames = 360;
  const double angle_step = 2 * M_PI / number_of_frames;

  for (size_t i = 0; i < number_of_frames; i++) {
    //std::cout << "Frame " << i << std::endl;
    // Rotate the mesh
    for (auto &vertex : mesh.get_vertices()){
      vertex = mesh::rotate_vertex(vertex,  rotation_line, angle_step);
    }

    // Create the output image
    std::string full_path_output_image = filename_without_suffix_output_frames + "-" + std::to_string(i) + ".png";

    // Paint the mesh
    mesh::painter_algorithm_with_textures(
      mesh,
      texture_image,
      full_path_output_image,
      -0.4,
      -0.4,
      0.4,
      0.4,
      400,
      400
    );
  }
}