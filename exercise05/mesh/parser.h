#include <string>
#include <fstream>
#include <memory>
#include "composite.h"
#include "json.h"
#include "exprtk.h"

#ifndef MESH_PARSER_H_
#define MESH_PARSER_H_
using json = nlohmann::json;
namespace mesh {
  class FunctionJSONParser{
    typedef std::function<double(double, double, double)> FunctionType;

    FunctionType function_evaluator;
    
    public:
    FunctionJSONParser(const std::string& json_string);
    double operator()(double x, double y, double z) const;
  };

  FunctionJSONParser function_from_file(const std::string& filename);


  class FunctionExpressionEvaluator{
    typedef double T;
    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T>   expression_t;
    typedef exprtk::parser<T>       parser_t;

    std::string expression_string;
    // Constructor
    public:
    FunctionExpressionEvaluator(const std::string& expression);
    // Functor
    double operator()(double ix, double iy, double iz);
  };
}

#endif // MESH_PARSER_H_