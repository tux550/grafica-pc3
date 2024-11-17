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





  FunctionExpressionEvaluator::FunctionExpressionEvaluator(const std::string& expression_string) {
    // Init variables
    x_ptr = std::make_shared<T>(0);
    y_ptr = std::make_shared<T>(0);
    z_ptr = std::make_shared<T>(0);
    // Reserve memory for symbol table and expression
    expression = std::make_shared<expression_t>();
    parser = std::make_shared<parser_t>();
    symbol_table = std::make_shared<symbol_table_t>();
    // Dummy symbol table
    symbol_table->add_variable("x",*x_ptr);
    symbol_table->add_variable("y",*y_ptr);
    symbol_table->add_variable("z",*z_ptr);
    // Register the symbol table
    expression->register_symbol_table(*symbol_table);
    // Compile the expression
    parser->compile(expression_string, *expression);
  }


  double FunctionExpressionEvaluator::operator()(double ix, double iy, double iz) {
    *(x_ptr) = ix;
    *(y_ptr) = iy;
    *(z_ptr) = iz;
    // Evaluate the expression
    auto res = expression->value();
    return res;
    
  }
}
