#include "composite.h"


namespace mesh{
  // Overload operator() to call the function
  double CompositeFunctor3D::operator()(double x, double y, double z) const {
    std::vector <double> values;
    for (auto& f : functions) {
      values.push_back(f(x, y, z));
    }

    // "union" performs the union of all the child objects.
    // "intersection" performs the intersection of all the child objects.
    // "diff" removes from the first child all the other childs.
    if (operation == UNION) {
      double result = values[0];
      for (size_t i = 1; i < values.size(); i++) {
        result = std::min(result, values[i]);
      }
      return result;
    } else if (operation == INTERSECT) {
      double result = values[0];
      for (size_t i = 1; i < values.size(); i++) {
        result = std::max(result, values[i]);
      }
      return result;
    } else if (operation == SUBSTRACT) {
      double result = values[0];
      for (size_t i = 1; i < values.size(); i++) {
        result = std::max(result, -values[i]);
      }
      return result;
    }
    else {
      throw std::runtime_error("Invalid operation type");
    }


    return 0;
  }
};
