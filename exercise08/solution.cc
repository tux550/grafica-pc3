#include "solution.h"
#include <set>
#include <map>

void catmull_clark(
    const std::string& full_path_input_mesh,
    int number_of_iterations,
    const std::string& full_path_output_mesh
) {
  // Load the input mesh
  mesh::Mesh base(full_path_input_mesh);

  // Apply the Catmull-Clark algorithm
  for (int i = 0; i < number_of_iterations; i++) {
    // New mesh
    std::vector<mesh::Face3D> new_faces;
    std::vector<mesh::Face3D> faces = base.get_faces();
    // Vertex related points
    std::map<mesh::Vertex3D, std::set<mesh::Vertex3D>> vertex_edgepoints;
    std::map<mesh::Vertex3D, std::set<mesh::Vertex3D>> vertex_facepoints;
    for (mesh::Vertex3D v : base.get_vertices()) {
      vertex_edgepoints[v] = {};
      vertex_facepoints[v] = {};
    }
    // Loop faces
    for (auto f : faces) {
      // Get Face points
      mesh::Vertex3D face_midpoint = f.get_midpoint();
      // Add face point to map
      for (auto v : f.vertices) {
        vertex_facepoints[v].insert(face_midpoint);
      }
      // Get Edge points
      std::vector<mesh::Vertex3D> edge_newpoints;
      std::vector<mesh::Edge3D> edges = f.get_edges();
      for (auto e : edges) {
        // Get faces with edge
        std::vector<mesh::Face3D> faces_with_edge = base.get_faces_with_edge(e);
        // Get values
        mesh::Vertex3D v0 = e.v1;
        mesh::Vertex3D v1 = e.v2;
        mesh::Vertex3D fm0 = faces_with_edge[0].get_midpoint();
        mesh::Vertex3D fm1 = faces_with_edge[1].get_midpoint();
        // Get edge
        mesh::Vertex3D edge_point = {
          (v0.x + v1.x + fm0.x + fm1.x) / 4.0f,
          (v0.y + v1.y + fm0.y + fm1.y) / 4.0f,
          (v0.z + v1.z + fm0.z + fm1.z) / 4.0f
        };
        edge_newpoints.push_back(edge_point);
        // Add edge midpoints to map
        mesh::Vertex3D edge_midpoint = e.get_midpoint();
        vertex_edgepoints[v0].insert(edge_midpoint);
        vertex_edgepoints[v1].insert(edge_midpoint);
      }
      // Get new faces
      for (int i = 0; i < f.vertices.size(); i++) {
        mesh::Vertex3D v0 = f.vertices[i];
        mesh::Vertex3D v1 = edge_newpoints[i];
        mesh::Vertex3D v2 = face_midpoint;
        mesh::Vertex3D v3 = edge_newpoints[(i + f.vertices.size() - 1) % f.vertices.size()];
        new_faces.push_back(mesh::Face3D({v0, v1, v2, v3}));
      }
    }
    // Get original points
    auto corners = base.get_vertices();
    // Update base
    base = mesh::Mesh(new_faces);
    // Update vertices
    for (auto corner: corners) {
      std::set<mesh::Vertex3D> edgepoints = vertex_edgepoints[corner];
      std::set<mesh::Vertex3D> facepoints = vertex_facepoints[corner];
      // F + 2R + (n-3)P / n
      // F=Average of face points
      // R=Average of edge midpoints
      // P=Current point
      // n=Number of edges/face
      int n = edgepoints.size();

      mesh::Vertex3D face_avg = {0, 0, 0};
      mesh::Vertex3D edge_avg = {0, 0, 0};
      for (auto f : facepoints) {
        face_avg.x += f.x;
        face_avg.y += f.y;
        face_avg.z += f.z;
      }
      for (auto e : edgepoints) {
        edge_avg.x += e.x;
        edge_avg.y += e.y;
        edge_avg.z += e.z;
      }
      face_avg.x /= n;
      face_avg.y /= n;
      face_avg.z /= n;
      edge_avg.x /= n;
      edge_avg.y /= n;
      edge_avg.z /= n;
      mesh::Vertex3D new_point = {
        (face_avg.x + 2*edge_avg.x + (n-3)*corner.x) / n,
        (face_avg.y + 2*edge_avg.y + (n-3)*corner.y) / n,
        (face_avg.z + 2*edge_avg.z + (n-3)*corner.z) / n
      };

      base.move_point(corner, new_point);
    }
  }

  // Save the mesh in same format as input
  base.save(full_path_output_mesh.c_str());
}