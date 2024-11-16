#include "solution.h"
#include <set>
#include <map>

void loop(
    const std::string& full_path_input_mesh,
    int number_of_iterations,
    const std::string& full_path_output_mesh
) {
  // Load the input mesh
  mesh::Mesh base(full_path_input_mesh);

  // Apply the Loop algorithm
  for (int i = 0; i < number_of_iterations; i++) {
    // New mesh
    std::vector<mesh::Face3D> new_faces;
    std::vector<mesh::Face3D> faces = base.get_faces();
    std::map<mesh::Vertex3D, std::vector<mesh::Vertex3D>> vertex_stars = base.get_stars(); //All adjacent vertices

    // Compute new corner points
    std::map<mesh::Vertex3D, mesh::Vertex3D> new_corners;
    for (auto [corner, star] : vertex_stars) {
      // Sum of all adjacent vertices
      mesh::Vertex3D sum = {0, 0, 0};
      for (auto v : star) {
        sum.x += v.x;
        sum.y += v.y;
        sum.z += v.z;
      }
      // Beta
      // n>3 => 3/8n
      // n=3 => 3/16
      double beta;
      if (star.size() > 3) {
        beta = 3.0f/ (8.0f * star.size());
      } else {
        beta = 3.0f/16.0f;
      }
      // New corner
      // v = (1 - n*beta) * v + beta * sum
      mesh::Vertex3D new_corner = {
        (1 - star.size() * beta) * corner.x + beta * sum.x,
        (1 - star.size() * beta) * corner.y + beta * sum.y,
        (1 - star.size() * beta) * corner.z + beta * sum.z
      };
      // Save new corner
      new_corners[corner] = new_corner;
    }


    for (auto f : faces) {
      // Get Edge points
      std::vector<mesh::Vertex3D> edge_newpoints;
      std::vector<mesh::Edge3D> edges = f.get_edges();
      // Map new edge points to corners
      std::map<mesh::Vertex3D, std::vector<mesh::Vertex3D>> vertex_edgepoints;
      // Vertex that create the center face
      std::vector<mesh::Vertex3D> center_face_vertexes;
      // Compute edge points
      for (auto e : edges) {
        // E = 3/8 * (V1 + V2) + 1/8 * (N1 + N2)
        // v1, v2 = edge vertices
        // n1, n2 = vertices of the two faces sharing the edge

        // Get N1 and N2
        // They are the vertex of each face that is not part of the edge
        auto  complementary_vertices = base.get_complementary_vertexes(e);
        mesh::Vertex3D n1 = complementary_vertices[0];
        mesh::Vertex3D n2 = complementary_vertices[1];

        // Get V1 and V2
        mesh::Vertex3D v1 = e.v1;
        mesh::Vertex3D v2 = e.v2;

        mesh::Vertex3D edge_point = {
          3.0f/8.0f * (v1.x + v2.x) + 1.0f/8.0f * (n1.x + n2.x),
          3.0f/8.0f * (v1.y + v2.y) + 1.0f/8.0f * (n1.y + n2.y),
          3.0f/8.0f * (v1.z + v2.z) + 1.0f/8.0f * (n1.z + n2.z)
        };

        // Add edge midpoints to map
        vertex_edgepoints[v1].push_back(edge_point);
        vertex_edgepoints[v2].push_back(edge_point);
        // Add to center face
        center_face_vertexes.push_back(edge_point);
      }
      // Create new faces looping over map
      for (auto [corner, edgepoints] : vertex_edgepoints) {
        // Get new corner
        mesh::Vertex3D new_corner = new_corners[corner];
        // Get edge points
        mesh::Vertex3D v1 = edgepoints[0];
        mesh::Vertex3D v2 = edgepoints[1];
        // Create face = {newcorner, edgepoint1, edgepoint2}
        auto new_face = mesh::Face3D({new_corner, v1, v2});
        // If not same direction as original face, reverse
        if ( dot_product(new_face.get_normal(), f.get_normal()) < 0) {
          new_face = mesh::Face3D({new_corner, v2, v1});
        }
        // Add face to new faces
        new_faces.push_back(new_face);
      }
      // Add center face
      auto center_face = mesh::Face3D(center_face_vertexes);
      if ( dot_product(center_face.get_normal(), f.get_normal()) < 0) {
        // Reverse center face
        std::reverse(center_face_vertexes.begin(), center_face_vertexes.end());
        center_face = mesh::Face3D(center_face_vertexes);
      }
      new_faces.push_back(center_face);
    }
    // Update base
    base = mesh::Mesh(new_faces);
  }

  // Save the mesh in same format as input
  base.save(full_path_output_mesh.c_str());
}