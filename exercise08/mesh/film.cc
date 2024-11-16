#include "film.h"

namespace mesh {
  bool Face2D::is_inside(Point2D const& point) const {
    // Check if the point is inside
    // if all cross products have the same sign, the point is inside
    // if at least one cross product has a different sign, the point is outside
    auto cross_product_sign = [](Point2D const& a, Point2D const& b, Point2D const& c) {
      return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    };
    auto same_sign = [](double a, double b) {
      return (a > 0 && b > 0) || (a < 0 && b < 0);
    };
    
    // Get first sign
    double sample_sign = cross_product_sign(vertices[0], vertices[1], point);

    for (size_t i = 1; i < vertices.size(); i++) {
      Point2D a = vertices[i];
      Point2D b = vertices[(i + 1) % vertices.size()];
      Point2D c = point;
      if (!same_sign(sample_sign, cross_product_sign(a, b, c))) {
        return false;
      }
    }
    return true;
  }

  // The projection plane is assumed to be at z = 1
  double ProjectionPlane::distance(Face3D & face) {
    // Maximum distance from the origin
    double max_distance = 0;
    for (Vertex3D& vertex : face.vertices) {
      double distance = vertex.magnitude();
      if (distance > max_distance) {
        max_distance = distance;
      }
    }
    return max_distance;
  }
  Point2D ProjectionPlane::project(Vertex3D const& vertex) const {
    double x = vertex.x / vertex.z;
    double y = vertex.y / vertex.z;
    return {x, y};
  }

  std::optional<Face2D> ProjectionPlane::project(Face3D const& face) const {
    Face2D face2d;
    // If at least one vertex is behind the projection plane, the face is not visible
    for (Vertex3D const& vertex : face.vertices) {
      if (vertex.z <= 0) {
        return std::nullopt;
      }
    }
    // Project each vertex to the projection plane
    for (Vertex3D const& vertex : face.vertices) {
      face2d.vertices.push_back(project(vertex));
    }
    return face2d;
  }
  Pixel ProjectionPlane::snap_to_pixel(Point2D const& point) const {
    double x = ((point.x - min_x) / (max_x - min_x)) * width_in_pixels;
    double y = ((point.y - min_y) / (max_y - min_y)) * height_in_pixels;
    return { static_cast<size_t>(x), static_cast<size_t>(y) };
  }

  Point2D ProjectionPlane::pixel_center(Pixel const& pixel) const {
    double x = min_x + (pixel.x + 0.5) * (max_x - min_x) / width_in_pixels;
    double y = min_y + (pixel.y + 0.5) * (max_y - min_y) / height_in_pixels;
    return {x, y};
  }

  void ProjectionPlane::draw_triangle(Face2D const& face, size_t ilumination) {
    // Get bounding box
    double b_min_x = min_x;
    double b_min_y = min_y;
    double b_max_x = max_x;
    double b_max_y = max_y;
    for (Point2D const& vertex : face.vertices) {
      b_min_x = std::min(b_min_x, vertex.x);
      b_min_y = std::min(b_min_y, vertex.y);
      b_max_x = std::max(b_max_x, vertex.x);
      b_max_y = std::max(b_max_y, vertex.y);
    }
    // Snap to pixels
    Pixel min_pixel = snap_to_pixel({b_min_x, b_min_y});
    Pixel max_pixel = snap_to_pixel({b_max_x, b_max_y});
    // Limit to the screen
    min_pixel.x = std::max(min_pixel.x, size_t(0));
    min_pixel.y = std::max(min_pixel.y, size_t(0));
    max_pixel.x = std::min(max_pixel.x, width_in_pixels - 1);
    max_pixel.y = std::min(max_pixel.y, height_in_pixels - 1);

    // Draw the triangle
    for (size_t x = min_pixel.x; x <= max_pixel.x; x++) {
      for (size_t y = min_pixel.y; y <= max_pixel.y; y++) {
        Point2D point = pixel_center({x, y});
        if (face.is_inside(point)) {
          image[x][y] = {ilumination, ilumination, ilumination};
        }
      }
    }
  }

  void ProjectionPlane::save_ppm(std::string const& filename) const {
    std::ofstream file;
    file.open(filename);
    file << "P3\n";
    file << width_in_pixels << " " << height_in_pixels << "\n";
    file << "255\n";
    for (size_t y = 0; y < height_in_pixels; y++) {
      for (size_t x = 0; x < width_in_pixels; x++) {
        file << image[x][y].r << " " << image[x][y].g << " " << image[x][y].b << " ";
      }
      file << "\n";
    }
    file.close();
  }

}