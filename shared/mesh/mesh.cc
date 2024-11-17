#include "mesh.h"
#include <string>
#include <sstream>

namespace mesh{
  void Mesh::set_texture_file(const std::string& filename) {
    texture_file = filename;
  }

  std::string Mesh::get_source_format() {
    return fileformat;
  }

  // Transform to generic Vertex3D
  Vertex3D Mesh::to_vertex(const MeshVertex& vertex) {
    return vertex;
  }

  // Transform to generic Face3D
  Face3D Mesh::to_face(const MeshFace& face) {
    std::vector<Vertex3D> vertices;
    for (int vertex_id : face.vertices) {
      vertices.push_back(get_vertex(vertex_id));
    }
    return Face3D(vertices, face.r, face.g, face.b);
  }

  // Insert vertex into mesh
  int Mesh::insert_vertex(const Vertex3D& vertex) {
    // Searcg for the vertex
    auto it = std::find(vertices.begin(), vertices.end(), vertex);
    if (it == vertices.end()) {
      // If the vertex is not found, add it
      vertices.push_back(vertex);
      return vertices.size() - 1;
    }
    else {
      return it - vertices.begin();
    }
  }

  // Insert face into mesh
  int Mesh::insert_face(const Face3D& face) {
    MeshFace mesh_face;
    for (Vertex3D vertex : face.vertices) {
      int vertex_id = insert_vertex(vertex);
      mesh_face.vertices.push_back(vertex_id);
    }
    mesh_face.r = face.r;
    mesh_face.g = face.g;
    mesh_face.b = face.b;
    faces.push_back(mesh_face);
    return faces.size() - 1;
  }

  // Void constructor
  Mesh::Mesh() {}

  // Constructor from generic Face3D
  Mesh::Mesh(const std::vector<Face3D>& faces) {
    // OPTIMIZED IMPLEMENTATION
    // Create a map of vertices
    std::map<Vertex3D, int> vertex_map;
    for (Face3D face : faces) {
      for (Vertex3D vertex : face.vertices) {
        // If the vertex is not in the map, add it
        if (vertex_map.find(vertex) == vertex_map.end()) {
          // Insert and register the vertex
          size_t vertex_id = vertices.size();
          vertices.push_back(vertex);
          vertex_map[vertex] = vertex_id;
        }
      }
    }
    // Create faces
    for (Face3D face : faces) {
      // Create face from map
      MeshFace mesh_face;
      for (Vertex3D vertex : face.vertices) {
        mesh_face.vertices.push_back(vertex_map[vertex]);
      }
      // Set color
      mesh_face.r = face.r;
      mesh_face.g = face.g;
      mesh_face.b = face.b;
      // Add face to mesh
      this->faces.push_back(mesh_face);
    }
    
    //for (Face3D face : faces) {
    //  insert_face(face);
    //}
  }

  // Load from PLY file
  void Mesh::load_ply(const std::string& filename) {
    std::ifstream file;
    file.open(filename);
    std::string line;
    // Set fileformat
    fileformat = "ply";
    // Read header
    std::getline(file, line);
    if (line != "ply") {
      std::cerr << "Invalid PLY file" << std::endl;
      return;
    }
    std::getline(file, line);
    if (line != "format ascii 1.0") {
      std::cerr << "Invalid PLY fileformat" << std::endl;
      return;
    }
    // Elements
    bool has_texture = false;
    std::vector<std::string> elements;
    std::map<std::string, int> element_count;
    std::getline(file, line);
    std::string current_element = "";
    while (line != "end_header"){
      // Split line by spaces
      std::istringstream iss(line);
      std::string t1, t2, t3;
      iss >> t1 >> t2 >> t3;
      // Determine input
      if (t1 == "element"){
        // Read element
        current_element = t2;
        auto current_count = std::stoi(t3);
        elements.push_back(current_element);
        element_count[current_element] = current_count;
      }
      else if (t1 == "property"){
        // skip
        if (t3 == "texture_u" || t3 == "texture_v"){
          has_texture = true;
        }
      }
      // Read next line
      std::getline(file, line);
    } 
    // Read vertices
    for (auto element : elements){
      if (element == "vertex"){
        for (int i = 0; i < element_count[element]; i++){
          std::getline(file, line);
          std::istringstream iss(line);
          double x, y, z;
          iss >> x >> y >> z;
          // If has texture, read texture coordinates
          if (has_texture){
            double u, v;
            iss >> u >> v;
            vertices.push_back(Vertex3D(x, y, z, u, v));
          }
          else {
            vertices.push_back(Vertex3D(x, y, z));
          }
        }
      }
      else if (element == "face"){
        for (int i = 0; i < element_count[element]; i++){
          std::getline(file, line);
          std::istringstream iss(line);
          int vertex_count;
          iss >> vertex_count;
          std::vector<int> vertex_ids;
          for (int j = 0; j < vertex_count; j++){
            int vertex_id;
            iss >> vertex_id;
            vertex_ids.push_back(vertex_id);
          }
          // If iss is not empty, read color
          int r, g, b;
          if (iss >> r >> g >> b){}
          else {
            // Default color
            r = 255;
            g = 255;
            b = 255;
          }
          // Create face
          MeshFace face;
          face.vertices = vertex_ids;
          face.r = r;
          face.g = g;
          face.b = b;
          faces.push_back(face);
        }
      }
      else {
        // Skip element
        for (int i = 0; i < element_count[element]; i++){
          std::getline(file, line);
        }
      }
    }
    // Close file
    file.close();
  }

  void Mesh::load_off(const std::string& filename) {
    std::ifstream file;
    file.open(filename);
    std::string line;
    // Set fileformat
    fileformat = "off";
    // Read header
    std::getline(file, line);
    if (line != "OFF") {
      std::cerr << "Invalid OFF file" << std::endl;
      return;
    }
    // Read vertices and faces
    int vertex_count, face_count, edge_count;
    file >> vertex_count >> face_count >> edge_count;
    // Read vertices
    for (int i = 0; i < vertex_count; i++) {
      double x, y, z;
      file >> x >> y >> z;
      vertices.push_back(Vertex3D(x, y, z));
    }
    // Read faces
    for (int i = 0; i < face_count; i++) {
      int vertex_count;
      file >> vertex_count;
      std::vector<int> vertex_ids;
      for (int j = 0; j < vertex_count; j++) {
        int vertex_id;
        file >> vertex_id;
        vertex_ids.push_back(vertex_id);
      }
      // Create face
      MeshFace face;
      face.vertices = vertex_ids;
      face.r = 255;
      face.g = 255;
      face.b = 255;
      faces.push_back(face);
    }
    // Close file
    file.close();
  }

  // Build mesh from file
  Mesh::Mesh(const std::string& filename) {
    // Determine file format
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    if (extension == "ply") {
      load_ply(filename);
    }
    else if (extension == "off") {
      load_off(filename);
    }
    else {
      std::cerr << "Invalid file format. Use PLY or OFF extension" << std::endl;
    }
  }

  // Generic getter for vertices
  std::vector<Vertex3D>& Mesh::get_vertices() {
    return vertices;
  }
  
  // Generic getter for faces
  std::vector<Face3D> Mesh::get_faces() {
    // From faces to Face3D
    std::vector<Face3D> face3d_faces;
    for (size_t i = 0; i < faces.size(); i++) {
      face3d_faces.push_back(get_face(i));
    }
    return face3d_faces;
  }

  Vertex3D Mesh::get_vertex(int index) {
    return vertices[index];
  }

  Face3D Mesh::get_face(int index) {
    return to_face(faces[index]);
  }

  // === To PLY ===
  std::string Mesh::get_ply_header(bool texture_coordinates) {
    std::string header = "ply\n";
    header += "format ascii 1.0\n";
    header += "element vertex " + std::to_string(vertices.size()) + "\n";
    if (texture_file != "") {
      header += "comment TextureFile " + texture_file + "\n";
    }
    header += "property double x\n";
    header += "property double y\n";
    header += "property double z\n";
    if (texture_coordinates) {
      header += "property double texture_u\n";
      header += "property double texture_v\n";
    }
    header += "element face " + std::to_string(faces.size()) + "\n";
    header += "property list uchar int vertex_index\n";
    header += "property uchar red\n";
    header += "property uchar green\n";
    header += "property uchar blue\n";
    header += "end_header\n";
    return header;
  }

  std::string Mesh::get_ply_vertex_string(bool texture_coordinates) {
    std::string vertex_string = "";
    for (Vertex3D vertex : vertices) {
      vertex_string += std::to_string(vertex.x) + " " + std::to_string(vertex.y) + " " + std::to_string(vertex.z);
      if (texture_coordinates) {
        vertex_string += " " + std::to_string(vertex.u) + " " + std::to_string(vertex.v);
      }
      vertex_string += "\n";
    }
    return vertex_string;
  }

  std::string Mesh::get_ply_face_string() {
    std::string face_string = "";
    for (MeshFace face : faces) {
      face_string += std::to_string(face.vertices.size()) + " ";
      for (int vertex_id : face.vertices) {
        face_string += std::to_string(vertex_id) + " ";
      }
      // RGB data
      face_string += std::to_string(face.r) + " " + std::to_string(face.g) + " " + std::to_string(face.b);
      face_string += "\n";
    }
    return face_string;
  }

  void Mesh::save_ply(const char* filename, bool texture_coordinates) {
    std::ofstream file;
    file.open(filename);
    file << get_ply_header(texture_coordinates);
    file << get_ply_vertex_string(texture_coordinates);
    file << get_ply_face_string();
    file.close();
  }

  std::string Mesh::get_off_header() {
    std::string header = "OFF\n";
    header += std::to_string(vertices.size()) + " " + std::to_string(faces.size()) + " 0\n";
    return header;
  }

  std::string Mesh::get_off_vertex_string() {
    std::string vertex_string = "";
    for (Vertex3D vertex : vertices) {
      vertex_string += std::to_string(vertex.x) + " " + std::to_string(vertex.y) + " " + std::to_string(vertex.z) + "\n";
    }
    return vertex_string;
  }

  std::string Mesh::get_off_face_string() {
    std::string face_string = "";
    for (MeshFace face : faces) {
      face_string += std::to_string(face.vertices.size()) + " ";
      for (int vertex_id : face.vertices) {
        face_string += std::to_string(vertex_id) + " ";
      }
      face_string += "\n";
    }
    return face_string;
  }


  void Mesh::save_off(const char* filename) {
    std::ofstream file;
    file.open(filename);
    file << get_off_header();
    file << get_off_vertex_string();
    file << get_off_face_string();
    file.close();
  }

  void Mesh::save(const char* filename) {
    std::string f = filename;
    // Determine file format
    std::string extension = f.substr(f.find_last_of(".") + 1);
    if (extension == "ply") {
      save_ply(filename);
    }
    else if (extension == "off") {
      save_off(filename);
    }
    else {
      std::cerr << "Invalid file format. Use PLY or OFF extension" << std::endl;
    }
  }


  // === Query ===
  std::vector<Face3D> Mesh::get_faces_with_edge(const Edge3D& edge) {
    std::vector<Face3D> faces_with_edge;
    for (MeshFace face : faces) {
      for (int i = 0; i < face.vertices.size(); i++) {
        Vertex3D v1 = get_vertex(face.vertices[i]);
        Vertex3D v2 = get_vertex(face.vertices[(i + 1) % face.vertices.size()]);
        Edge3D forward_edge = Edge3D(v1, v2);
        Edge3D reversed_edge = forward_edge.reversed();
        if (forward_edge == edge || reversed_edge == edge) {
          faces_with_edge.push_back( to_face(face) );
          break;
        }
      }
    }
    return faces_with_edge;
  }

  std::vector<Vertex3D> Mesh::get_complementary_vertexes(const Edge3D& edge) {
    Vertex3D v1 = edge.v1;
    Vertex3D v2 = edge.v2;
    std::vector<Face3D> faces_with_edge = get_faces_with_edge(edge);
    std::vector<Vertex3D> complementary_vertexes;
    for (Face3D face : faces_with_edge) {
      for (Vertex3D vertex : face.vertices) {
        if (vertex != v1 && vertex != v2) {
          complementary_vertexes.push_back(vertex);
        }
      }
    }
    return complementary_vertexes;
  }

  std::map<Vertex3D, std::vector<Vertex3D>> Mesh::get_stars() {
    std::map<Vertex3D, std::vector<Vertex3D>> stars;
    for (MeshFace face : faces) {
      for (int i = 0; i < face.vertices.size(); i++) {
        Vertex3D v1 = get_vertex(face.vertices[i]);
        Vertex3D v2 = get_vertex(face.vertices[(i + 1) % face.vertices.size()]);
        stars[v1].push_back(v2);
        stars[v2].push_back(v1);
      }
    }
    return stars;
  }

  // Modify mesh
  void Mesh::move_point(const Vertex3D& point, const Vertex3D& target) {
    // Search for the point
    auto it = std::find(vertices.begin(), vertices.end(), point);
    if (it != vertices.end()) {
      // If the point is found, move it
      *it = target;
    }
  }

  // Displace
  void Mesh::displace(const Vertex3D& v) {
    for (Vertex3D& vertex : vertices) {
      vertex = vertex + v;
    }
  }
  
  // Rotate
  void Mesh::rotate(Line3D& axis, double angle) {
    for (Vertex3D& vertex : vertices) {
      // Rotate around axis
      vertex = rotate_vertex(vertex, axis, angle);
    }
  }
}