// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "opencv2/opencv.hpp"
#include "mesh/mesh.h"
#include "mesh/film.h"
#include "mesh/painter.h"


void painter_algorithm_textures(
std::string const& full_path_input_mesh,
std::string const& full_path_input_texture,
std::string const& full_path_output_image,
double min_x_coordinate_in_projection_plane,
double min_y_coordinate_in_projection_plane,
double max_x_coordinate_in_projection_plane,
double max_y_coordinate_in_projection_plane,
size_t width_in_pixels,
size_t height_in_pixels);