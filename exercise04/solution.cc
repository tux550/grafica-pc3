#include "solution.h"

void sphere_with_triangular_faces(
  std::string const& full_path_output_file,
  double radius,
  double center_x, double center_y, double center_z,
  int step_size
) {

  std::vector<mesh::Face3D> faces;
  // Lambda to turn from degrees to radians
  auto deg_to_rad = [](double deg) { return deg * M_PI / 180.0; };
  // All integer values of alpha and beta in the range [0, 360)
  

  for (int alpha = 0; alpha < 360; alpha += step_size) {
    for (int beta = 0; beta < 180; beta += step_size) {
      double a1 = deg_to_rad( alpha           );
      double a2 = deg_to_rad((alpha + step_size) % 360);
      double b1 = deg_to_rad(beta            );
      double b2 = deg_to_rad((beta  + step_size) % 360);

      // Alpha: angle formed with the y-z plane
      // Beta: angle formed with the (0, 0, -1) vector


      // Get vertex coordinates lambda
      auto get_vertex = [&](double a, double b) {
        return mesh::Vertex3D(
          radius * std::sin(b) * std::cos(a),
          radius * std::sin(b) * std::sin(a),
          radius * std::cos(b)
        );
      };

      if (beta == 0) {
        // b1 is the north pole
        // Faces: (a1, b1), (a1, b2), (a2, b2)
        faces.push_back(mesh::Face3D({
          get_vertex(a1, b1),
          get_vertex(a1, b2),
          get_vertex(a2, b2)
        }));
      }
      else if (beta == 180 - step_size) {
        // b2 is the south pole
        // Faces: (a1, b1), (a1, b2), (a2, b1)
        faces.push_back(mesh::Face3D({
          get_vertex(a1, b1),
          get_vertex(a1, b2),
          get_vertex(a2, b1)
        }));
      }
      else {
        // Faces: 
        // T1 - (a1, b1), (a1, b2), (a2, b2)
        // T2 - (a2, b2), (a2, b1), (a1, b1)
        faces.push_back(mesh::Face3D({
          get_vertex(a1, b1),
          get_vertex(a1, b2),
          get_vertex(a2, b2)
        }));
        faces.push_back(mesh::Face3D({
          get_vertex(a2, b2),
          get_vertex(a2, b1),
          get_vertex(a1, b1)
        }));
      }
    }
  }
  // To mesh
  mesh::Mesh mesh(faces);
  // Displace by center
  mesh.displace(mesh::Vertex3D(center_x, center_y, center_z));
  // Write to file
  mesh.save_ply(full_path_output_file.c_str());
}