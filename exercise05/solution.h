// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include "mesh/mesh.h"
#include "mesh/3d.h"
#include <tuple>

void sphere_with_texture(
    const std::string& full_path_input_ply,
    const std::string& full_path_texture,
    const std::tuple<double, double, double>& center,
    const std::string& full_path_output_ply
);