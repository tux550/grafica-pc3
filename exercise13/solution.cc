#include "solution.h"
#include <set>
#include <map>

void painter_algorithm_textures(
std::string const& full_path_input_mesh,
std::string const& full_path_input_texture,
std::string const& full_path_output_image,
double min_x_coordinate_in_projection_plane,
double min_y_coordinate_in_projection_plane,
double max_x_coordinate_in_projection_plane,
double max_y_coordinate_in_projection_plane,
size_t width_in_pixels,
size_t height_in_pixels){
  // Load the mesh
  mesh::Mesh mesh(full_path_input_mesh);

  // Load matrix texture using opencv
  cv::Mat texture_image = cv::imread(full_path_input_texture, cv::IMREAD_COLOR);

  mesh::painter_algorithm_with_textures(
    mesh,
    texture_image,
    full_path_output_image,
    min_x_coordinate_in_projection_plane,
    min_y_coordinate_in_projection_plane,
    max_x_coordinate_in_projection_plane,
    max_y_coordinate_in_projection_plane,
    width_in_pixels,
    height_in_pixels
  );
}