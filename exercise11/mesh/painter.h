#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "mesh.h"
#include <opencv2/opencv.hpp>

#ifndef SHARED_MESH_PAINTER_H
#define SHARED_MESH_PAINTER_H

namespace mesh {
  void painter_algorithm_with_textures(
    std::string const& full_path_input_mesh,
    std::string const& full_path_texture,
    std::string const& full_path_output_image,
    double min_x_coordinate_in_projection_plane,
    double min_y_coordinate_in_projection_plane,
    double max_x_coordinate_in_projection_plane,
    double max_y_coordinate_in_projection_plane,
    size_t width_in_pixels,
    size_t height_in_pixels);
}

#endif // SHARED_MESH_PAINTER_H