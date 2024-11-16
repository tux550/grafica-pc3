// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>

#include <string>
#include "mesh/mesh.h"
#include "mesh/3d.h"


void loop(
    const std::string& full_path_input_mesh,
    int number_of_iterations,
    const std::string& full_path_output_mesh
);