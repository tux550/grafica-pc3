#include <vector>
#include <optional>
#include <math.h>
#include "3d.h"

#ifndef MESH_FILM_H
#define MESH_FILM_H
namespace mesh {
  struct Point2D {
    double x, y;
  };

  struct Face2D {
    std::vector<Point2D> vertices;

    bool is_inside(Point2D const& point) const;
  };

  struct Pixel {
    size_t x, y;
  };

  struct RGB {
    size_t r, g, b;
  };

  class ProjectionPlane {
  private:
    double min_x, min_y, max_x, max_y;
    size_t width_in_pixels, height_in_pixels;
    std::vector<std::vector<RGB>> image;

  public:
    ProjectionPlane(
      double min_x,
      double min_y,
      double max_x,
      double max_y,
      size_t width_in_pixels,
      size_t height_in_pixels):
      min_x(min_x),
      min_y(min_y),
      max_x(max_x),
      max_y(max_y),
      width_in_pixels(width_in_pixels),
      height_in_pixels(height_in_pixels),
      image(width_in_pixels, std::vector<RGB>(height_in_pixels, {0, 0, 0})) {}
    
    double distance(Face3D & face);
    Point2D project(Vertex3D const& vertex) const;
    std::optional<Face2D> project(Face3D const& face) const;
    Pixel snap_to_pixel(Point2D const& point) const;
    Point2D pixel_center(Pixel const& pixel) const;
    void draw_triangle(Face2D const& face, size_t ilumination);

    void save_ppm(std::string const& filename) const;
  };
}
#endif
