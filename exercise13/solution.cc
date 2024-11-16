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
  mesh::painter_algorithm_with_textures(
    full_path_input_mesh,
    full_path_input_texture,
    full_path_output_image,
    min_x_coordinate_in_projection_plane,
    min_y_coordinate_in_projection_plane,
    max_x_coordinate_in_projection_plane,
    max_y_coordinate_in_projection_plane,
    width_in_pixels,
    height_in_pixels
  );
}