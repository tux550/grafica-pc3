#include "film.h"

namespace mesh {
  Point2D Point2D::operator-(Point2D const& other) const {
    return {x - other.x, y - other.y};
  }
  Point2D Point2D::operator+(Point2D const& other) const {
    return {x + other.x, y + other.y};
  }

  double cross_product(Point2D const& a, Point2D const& b) {
    return a.x * b.y - a.y * b.x;
  }

  bool Face2D::is_inside(Point2D const& point) const {
    // Check if the point is inside
    // if all cross products have the same sign, the point is inside
    // if at least one cross product has a different sign, the point is outside
    auto same_sign = [](double a, double b) {
      return (a > 0 && b > 0) || (a < 0 && b < 0);
    };

    auto cross_product_sign = [](Point2D const& a, Point2D const& b, Point2D const& c) {
      return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
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
    return {x, y, vertex.u, vertex.v};
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

  size_t ProjectionPlane::snap_y_to_pixel(double y) const {
    double y_normalized = (y - min_y) / (max_y - min_y);
    return static_cast<size_t>(y_normalized * height_in_pixels);
  }

  size_t ProjectionPlane::snap_x_to_pixel(double x) const {
    double x_normalized = (x - min_x) / (max_x - min_x);
    return static_cast<size_t>(x_normalized * width_in_pixels);
  }

  Pixel ProjectionPlane::snap_to_pixel(Point2D const& point) const {
    double x = snap_x_to_pixel(point.x);
    double y = snap_y_to_pixel(point.y);
    return { static_cast<size_t>(x), static_cast<size_t>(y) };
  }




  Point2D ProjectionPlane::pixel_center(Pixel const& pixel) const {
    double x = min_x + (pixel.x + 0.5) * (max_x - min_x) / width_in_pixels;
    double y = min_y + (pixel.y + 0.5) * (max_y - min_y) / height_in_pixels;
    return {x, y};
  }

  double ProjectionPlane::y_center(size_t y) const {
    return min_y + (y + 0.5) * (max_y - min_y) / height_in_pixels;
  }

  void ProjectionPlane::draw_triangle(Face2D const& face, size_t ilumination) {
    // Get bounding box
    double b_min_y = min_y;
    double b_max_y = max_y;
    for (Point2D const& vertex : face.vertices) {
      b_min_y = std::min(b_min_y, vertex.y);
      b_max_y = std::max(b_max_y, vertex.y);
    }
    // Snap to pixels
    size_t min_y_pixel = std::max(snap_y_to_pixel(b_min_y), size_t(0));
    size_t max_y_pixel = std::min(snap_y_to_pixel(b_max_y), height_in_pixels - 1);
    
    // Draw the triangle
    for (size_t y = min_y_pixel; y <= max_y_pixel; y++) {
      auto [min_x_pixel, max_x_pixel] = compute_x_bounds_for_y(face, y);
      for (size_t x = min_x_pixel; x <= max_x_pixel; x++) {
        Point2D point = pixel_center({x, y});
        if (face.is_inside(point)) {
          image[x][y] = {ilumination, ilumination, ilumination};
        }
      }
    }
  }

  void ProjectionPlane::draw_triangle_with_texture(Face2D const& face, double ilumination, cv::Mat const& texture) {
    // Get y-limits
    double b_min_y = min_y;
    double b_max_y = max_y;
    for (Point2D const& vertex : face.vertices) {
      b_min_y = std::min(b_min_y, vertex.y);
      b_max_y = std::max(b_max_y, vertex.y);
    }

    // Snap to pixels
    size_t min_y_pixel = std::max(snap_y_to_pixel(b_min_y), size_t(0));
    size_t max_y_pixel = std::min(snap_y_to_pixel(b_max_y), height_in_pixels - 1);

    // Draw
    for (size_t y = min_y_pixel; y <= max_y_pixel; y++) {
      auto [min_x_pixel, max_x_pixel] = compute_x_bounds_for_y(face, y);
      for (size_t x = min_x_pixel; x <= max_x_pixel; x++) {
        // Get the pixel center
        Point2D point = pixel_center({x, y});
        // Calculate barycentric coordinates

        // Assuming triangle
        double area_total = (face.vertices[1].x - face.vertices[0].x) * (face.vertices[2].y - face.vertices[0].y) - (face.vertices[2].x - face.vertices[0].x) * (face.vertices[1].y - face.vertices[0].y);
        if (area_total == 0) {
          continue;
        }
        double alpha = ((face.vertices[1].x - point.x) * (face.vertices[2].y - point.y) - (face.vertices[2].x - point.x) * (face.vertices[1].y - point.y)) / area_total;
        double beta = ((face.vertices[2].x - point.x) * (face.vertices[0].y - point.y) - (face.vertices[0].x - point.x) * (face.vertices[2].y - point.y)) / area_total;
        double gamma = 1 - alpha - beta;

        // Get texture coordinates
        double iu = alpha * face.vertices[0].u + beta * face.vertices[1].u + gamma * face.vertices[2].u;
        double iv = alpha * face.vertices[0].v + beta * face.vertices[1].v + gamma * face.vertices[2].v;

        // Limit u,v to [0, 1]
        double u = std::max(std::min(iu, 1.0), 0.0);
        double v = std::max(std::min(iv, 1.0), 0.0);

        // Get texture color
        size_t texture_x = u * (texture.cols-1);
        size_t texture_y = v * (texture.rows-1);
        cv::Vec3b color_cv = texture.at<cv::Vec3b>(texture_y, texture_x);
        RGB color = {color_cv[2], color_cv[1], color_cv[0]};


        // Apply ilumination
        color.r = static_cast<size_t>(color.r * ilumination);
        color.g = static_cast<size_t>(color.g * ilumination);
        color.b = static_cast<size_t>(color.b * ilumination);

        // Draw the pixel
        image[x][y] = color;
        
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

  void ProjectionPlane::save_png(std::string const& filename) const {
    cv::Mat image_cv(height_in_pixels, width_in_pixels, CV_8UC3);
    for (size_t y = 0; y < height_in_pixels; y++) {
      for (size_t x = 0; x < width_in_pixels; x++) {
        image_cv.at<cv::Vec3b>(y, x) = {image[x][y].b, image[x][y].g, image[x][y].r};
      }
    }
    cv::imwrite(filename, image_cv);
  }


  
  std::tuple<size_t, size_t> ProjectionPlane::compute_x_bounds_for_y(const Face2D& face, size_t y_pixel) {
    std::vector<double> x_intersections;
    double y = y_center(y_pixel);
    for (size_t i = 0; i < face.vertices.size(); i++) {
      const Point2D& p1 = face.vertices[i];
      const Point2D& p2 = face.vertices[(i + 1) %  face.vertices.size()];
      // Check if edge intersects the horizontal line at y
      if ((y >= std::min(p1.y, p2.y)) && (y <= std::max(p1.y, p2.y))) {
        // Avoid division by zero if the edge is horizontal
        if (p1.y != p2.y) {
          // Compute x-intersection
          double t = (y - p1.y) / (p2.y - p1.y); // Interpolation factor
          double x = p1.x + t * (p2.x - p1.x);
          x_intersections.push_back(x);
        } else {
          // Horizontal edge: add both endpoints
          x_intersections.push_back(p1.x);
          x_intersections.push_back(p2.x);
        }
      }
    }
    // If empty, return invalid bounds
    if (x_intersections.empty()) {
      return {1, 0};
    }
    // If only one intersection, return it
    if (x_intersections.size() == 1) {
      return {snap_x_to_pixel(x_intersections[0]), snap_x_to_pixel(x_intersections[0])};
    }

    // Find min and max x from the intersections
    double x_min = *std::min_element(x_intersections.begin(), x_intersections.end());
    double x_max = *std::max_element(x_intersections.begin(), x_intersections.end());
    // Snap to pixels
    size_t x_min_pixel = snap_x_to_pixel(x_min);
    size_t x_max_pixel = snap_x_to_pixel(x_max);

    // Limit to the screen
    x_min_pixel = std::max(x_min_pixel, size_t(0));
    x_max_pixel = std::min(x_max_pixel, width_in_pixels - 1);

    return {x_min_pixel, x_max_pixel};
  }
}