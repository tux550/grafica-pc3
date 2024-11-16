#include <gtest/gtest.h>
#include "solution.h"
#include "mesh/parser.h"
#include "mesh/json.h"

TEST(parser_test, read_json) {
  std::string example_json = R"(
  {
    "op": "union",
    "function": "",
    "childs": [
      {
        "op": "",
        "function": "(x+1)^2 + (y-3)^2 - 4^2",
        "childs": []
      },
      {
        "op": "",
        "function": "(x-2)^2 + (y+1)^2 - 4^2",
        "childs": []
      }
    ]
  })";

  json j = json::parse(example_json);
  // Get operation, function and childs
  std::string operation = j["op"];
  std::string function = j["function"];
  json childs = j["childs"];
  // Assert operation is union
  EXPECT_EQ(operation, "union");
  // Assert function is empty
  EXPECT_TRUE(function.empty());
  // Assert childs is not empty
  EXPECT_FALSE(childs.empty());

}

TEST(parser_test, composite_from_file) {
  // Load file example.json
  const std::string filename = "example.json";
  auto func = mesh::function_from_file(filename);

  // Evaluate function
  double x = 1.0, y = 2.0, z = 3.0;
  double result = func(x, y, z);
  // Validate negative result
  std::cout << "result1: " << result << std::endl;
  EXPECT_LT(result, 0.0);
  
  x = -2.0, y = 0.0, z = -4.0;
  // Validate negative result
  result = func(x, y, z);
  std::cout << "result2: " << result << std::endl;
  EXPECT_LT(result, 0.0);

  x = 0.0, y = -10.0, z = 0.0;
  // Validate positive result
  result = func(x, y, z);
  std::cout << "result3: " << result << std::endl;
  EXPECT_GT(result, 0.0);


}
/*
TEST(lib_test, basic_polynomial) {
  // Eval function at x=1, y=2, z=3

  const std::string eval_string = "x^2 + y^2 + z^2";
  symbol_table_t symbol_table;
  double x;
  double y;
  double z;

  symbol_table.add_variable("x", x);
  symbol_table.add_variable("y", y);
  symbol_table.add_variable("z", z);

  expression_t expression;
  expression.register_symbol_table(symbol_table);

  parser_t parser;
  parser.compile(eval_string, expression);

  x = 1.0;
  y = 2.0;
  z = 3.0;

  double result = expression.value();
  double expected = x*x + y*y + z*z;

  std::cout << "result: " << result << std::endl;
  std::cout << "expected: " << expected << std::endl;

  EXPECT_DOUBLE_EQ(result, expected);
}
*/

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}