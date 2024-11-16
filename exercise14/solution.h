// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include "mesh/mesh.h"
#include "mesh/film.h"
#include "mesh/painter.h"


void frames_of_a_textured_sphere_rotating(
std::string const& full_path_input_mesh,
std::string const& full_path_input_texture,
double rotation_line_point_x,
double rotation_line_point_y,
double rotation_line_point_z,
double rotation_line_direction_x,
double rotation_line_direction_y,
double rotation_line_direction_z,
std::string const& filename_without_suffix_output_frames);