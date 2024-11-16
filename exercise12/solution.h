// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include "mesh/mesh.h"
#include "mesh/film.h"


void painter_algorithm_simple_cosine_illumination(
std::string const& full_path_input_mesh,
std::string const& full_path_output_image,
double min_x_coordinate_in_projection_plane,
double min_y_coordinate_in_projection_plane,
double max_x_coordinate_in_projection_plane,
double max_y_coordinate_in_projection_plane,
size_t width_in_pixels,
size_t height_in_pixels);