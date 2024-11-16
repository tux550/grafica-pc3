// Make math constants available
#define _USE_MATH_DEFINES
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <random>
#include <algorithm>
#include "mesh/mesh.h"
#include "mesh/3d.h"
#include "mesh/parser.h" 

#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H

#define DEBUG_COLOR

using namespace mesh;

using CubeVertexes = std::array<Vertex3D, 8>;
using CubeColors = std::array<bool, 8>;


void marching_cubes(
    const std::string& json_object_describing_surface,
    const std::string& output_filename,
    double x_min, double y_min,
    double x_max, double y_max,
    double z_min, double z_max,
    double precisions
);

// == UTILITY FUNCTIONS ==
Vertex3D getCenter(const CubeVertexes& cube);


Vertex3D weightedMidpoint(const Vertex3D& a, const Vertex3D& b, std::function<double(double, double, double)> func);


double getSign(double value);

double getColor(double value);

double getColor(
  std::function<double(double, double, double)> func,
  CubeVertexes cube,
  size_t index);



void flipColors(CubeColors& colors);


// Front face 0-3 in counter-clockwise order, back face 4-7 in counter-clockwise order
// Return neighbors in counter-clockwise order
std::vector<size_t> getVertexNeighbors(size_t index);


size_t getOppositeVertex(size_t index);


Vertex3D getVertex(size_t index);


bool pointingSameDirection(Vertex3D a,  Vertex3D b, Vertex3D c, Vertex3D dir_vec);


std::vector<size_t> getVertexNeighborsExcluding(size_t index, const std::vector<size_t> &exclude);


bool vertexAreAdjacent(size_t a, size_t b);


std::vector<std::vector<size_t>> getAdyacentColoredVertices(const CubeColors& colors);


std::vector<Face3D> getFacesVertex1(const CubeVertexes& cube, std::vector<size_t> vertex_indexes, std::function<double(double, double, double)> func);


std::vector<Face3D> getFacesVertex2(const CubeVertexes& cube, std::vector<size_t> vertex_indexes, std::function<double(double, double, double)> func);


std::vector<Face3D> getFacesVertex3(const CubeVertexes& cube, std::vector<size_t> vertex_indexes, std::function<double(double, double, double)> func);

std::vector<Face3D> getFacesVertex4(const CubeVertexes& cube, std::vector<size_t> vertex_indexes, std::function<double(double, double, double)> func);


std::vector<Face3D> cubeCases(
  CubeVertexes cube,
  std::function<double(double, double, double)> func
);

std::vector<Face3D> adaptativeMarchingCubes(
  std::function<double(double, double, double)> func,
  double x_start,
  double y_start,
  double z_start,
  double x_end,
  double y_end,
  double z_end,
  double precision,
  size_t samples = 200
);
#endif