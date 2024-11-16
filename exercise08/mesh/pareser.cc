#include "json.h"
#include "parser.h"



namespace mesh {
  FunctionJSONParser function_from_file(const std::string& filename){
    // Read the JSON
    std::ifstream file(filename);
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
      content += line;
    }
    return FunctionJSONParser(content);
  }

  FunctionJSONParser::FunctionJSONParser(const std::string& json_string) {
    // Parse the JSON content
    json j = json::parse(json_string);
    // Get operation, function and childs
    std::string operation = j["op"];
    std::string function = j["function"];
    json childs = j["childs"];
    // If operation is empty, then it is a base function
    if (operation.empty()) {
      // Set the function
      function_evaluator = FunctionExpressionEvaluator(function);
    } else {
      // Get the operation type
      OperationType op;
      if (operation == "union") {
        op = UNION;
      } else if (operation == "intersection") {
        op = INTERSECT;
      } else if (operation == "diff") {
        op = SUBSTRACT;
      }
      else {
        throw std::runtime_error("Invalid operation type");
      }
      // Create a composite functor
      CompositeFunctor3D composite;
      // Set the operation
      composite.operation = op;
      // Fill the vector of functions
      for (auto& child : childs) {
        // Create a function expression evaluator
        FunctionJSONParser f(child.dump());
        // Add the function to the vector
        composite.functions.push_back( FunctionJSONParser(child.dump()) );
      }
      // Set the function to composite
      function_evaluator = composite;
    }
  }

  double FunctionJSONParser::operator()(double x, double y, double z) const {
    // Call the function
    return function_evaluator(x, y, z);
  }





  FunctionExpressionEvaluator::FunctionExpressionEvaluator(const std::string& expression_string) : expression_string(expression_string) {}


  double FunctionExpressionEvaluator::operator()(double ix, double iy, double iz) {
    symbol_table_t symbol_table;
    expression_t expression;
    parser_t parser;

    // Initialize symbol table, parser and expression
    symbol_table.add_variable("x", ix, true);
    symbol_table.add_variable("y", iy, true);
    symbol_table.add_variable("z", iz, true);
    expression.register_symbol_table(symbol_table);
    parser.compile(expression_string, expression);

    // Evaluate the expression
    auto res = expression.value();
    std::cout << "Result of evaluating x=" << ix << ", y=" << iy << ", z=" << iz << " in " << expression_string << " is " << res << std::endl;
    return res;
    
  }
}
