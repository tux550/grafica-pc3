// Composite functions

#ifndef MESH_COMPOSITE_H_
#define MESH_COMPOSITE_H_

#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>

namespace mesh{

enum OperationType {
  UNION,
  INTERSECT,
  SUBSTRACT,
};


struct CompositeFunctor3D {
  typedef std::function<double(double, double, double)> FunctionType;

  std::vector<FunctionType> functions;
  
  OperationType operation;

  // Constructor
  CompositeFunctor3D(const std::vector<FunctionType>& functions, OperationType operation) : functions(functions), operation(operation) {}
  CompositeFunctor3D() = default;

  // Overload operator() to call the function
  double operator()(double x, double y, double z) const;
};


}; // namespace mesh


#endif // MESH_COMPOSITE_H_