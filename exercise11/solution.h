// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include "mesh/mesh.h"
#include "mesh/3d.h"

void marching_cubes(
    const std::string& json_object_describing_surface,
    const std::string& output_filename,
    double x_min, double y_min,
    double x_max, double y_max,
    double z_min, double z_max,
    double precisions
);