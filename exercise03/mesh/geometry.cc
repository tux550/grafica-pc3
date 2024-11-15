#include "geometry.h"

namespace mesh {
  Mesh unitCircleCube() {
    // Vertex
    // -1 -1 -1
    // -1 1 -1
    // 1 1 -1
    // 1 -1 -1
    // -1 -1 1
    // -1 1 1
    // 1 1 1
    // 1 -1 1
    double d = std::sqrt(1.0f/3.0f);
    std::vector<Vertex3D> v = {
      Vertex3D(-d, -d, -d),
      Vertex3D(-d, d, -d),
      Vertex3D(d, d, -d),
      Vertex3D(d, -d, -d),
      Vertex3D(-d, -d, d),
      Vertex3D(-d, d, d),
      Vertex3D(d, d, d),
      Vertex3D(d, -d, d)
    };
    // Faces
    // 3 7 4 0
    // 1 0 4 5
    // 4 7 6 5
    // 1 2 3 0
    // 3 2 6 7
    // 6 2 1 5
    std::vector<Face3D> f = {
      Face3D({v[3], v[7], v[4], v[0]}),
      Face3D({v[1], v[0], v[4], v[5]}),
      Face3D({v[4], v[7], v[6], v[5]}),
      Face3D({v[1], v[2], v[3], v[0]}),
      Face3D({v[3], v[2], v[6], v[7]}),
      Face3D({v[6], v[2], v[1], v[5]})
    };

    return Mesh(f);
  }


  Mesh unitCircleTetrahedron() {
    // Vertex of tetrahedron
    // > (0, 0, 0)
    // > (0, 1, 1)
    // > (1, 0, 1)
    // > (1, 1, 0)
    // Faces of tetrahedron
    // > v0, v1, v3
    // > v0, v3, v2
    // > v0, v2, v1
    // > v1, v2, v3
    double d = std::sqrt(1.0f/3.0f);

    std::vector<Vertex3D> v = {
      Vertex3D(-d, -d, -d),
      Vertex3D(-d, d, d),
      Vertex3D(d, -d, d),
      Vertex3D(d, d, -d)
    };
    std::vector<Face3D> f = {
      Face3D({v[0], v[1], v[3]}),
      Face3D({v[0], v[3], v[2]}),
      Face3D({v[0], v[2], v[1]}),
      Face3D({v[1], v[2], v[3]})
    };

    return Mesh(f);
  }


  Mesh cuboidSquaredFaces(
    double min_x, double max_x,
    double min_y, double max_y,
    double min_z, double max_z
  ) {
    // Vertex
    // -1 -1 -1
    // -1 1 -1
    // 1 1 -1
    // 1 -1 -1
    // -1 -1 1
    // -1 1 1
    // 1 1 1
    // 1 -1 1
    std::vector<Vertex3D> v = {
      Vertex3D(-min_x, -min_y, -min_z),
      Vertex3D(-min_x, max_y, -min_z),
      Vertex3D(max_x, max_y, -min_z),
      Vertex3D(max_x, -min_y, -min_z),
      Vertex3D(-min_x, -min_y, max_z),
      Vertex3D(-min_x, max_y, max_z),
      Vertex3D(max_x, max_y, max_z),
      Vertex3D(max_x, -min_y, max_z)
    };
    // Faces
    // 3 7 4 0
    // 1 0 4 5
    // 4 7 6 5
    // 1 2 3 0
    // 3 2 6 7
    // 6 2 1 5
    std::vector<Face3D> f = {
      Face3D({v[3], v[7], v[4], v[0]}),
      Face3D({v[1], v[0], v[4], v[5]}),
      Face3D({v[4], v[7], v[6], v[5]}),
      Face3D({v[1], v[2], v[3], v[0]}),
      Face3D({v[3], v[2], v[6], v[7]}),
      Face3D({v[6], v[2], v[1], v[5]})
    };
    return Mesh(f);
  }

  
  Mesh cuboidTriangularFaces(
    double min_x, double max_x,
    double min_y, double max_y,
    double min_z, double max_z
  ) {
    // Vertex
    // -1 -1 -1
    // -1 1 -1
    // 1 1 -1
    // 1 -1 -1
    // -1 -1 1
    // -1 1 1
    // 1 1 1
    // 1 -1 1
    std::vector<Vertex3D> v = {
      Vertex3D(-min_x, -min_y, -min_z),
      Vertex3D(-min_x, max_y, -min_z),
      Vertex3D(max_x, max_y, -min_z),
      Vertex3D(max_x, -min_y, -min_z),
      Vertex3D(-min_x, -min_y, max_z),
      Vertex3D(-min_x, max_y, max_z),
      Vertex3D(max_x, max_y, max_z),
      Vertex3D(max_x, -min_y, max_z)
    };
    // Faces
    // 3 7 4
    // 4 0 3
    // 1 0 4
    // 4 5 1
    // 4 7 6
    // 6 5 4
    // 1 2 3
    // 3 0 1
    // 3 2 6
    // 6 7 3
    // 6 2 1
    // 1 5 6 
    std::vector<Face3D> f = {
      Face3D({v[3], v[7], v[4]}),
      Face3D({v[4], v[0], v[3]}),
      Face3D({v[1], v[0], v[4]}),
      Face3D({v[4], v[5], v[1]}),
      Face3D({v[4], v[7], v[6]}),
      Face3D({v[6], v[5], v[4]}),
      Face3D({v[1], v[2], v[3]}),
      Face3D({v[3], v[0], v[1]}),
      Face3D({v[3], v[2], v[6]}),
      Face3D({v[6], v[7], v[3]}),
      Face3D({v[6], v[2], v[1]}),
      Face3D({v[1], v[5], v[6]})
    };
    return Mesh(f);
  }
}