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
  EXPECT_LT(result, 0.0);
  
  x = -2.0, y = 0.0, z = -4.0;
  // Validate negative result
  result = func(x, y, z);
  EXPECT_LT(result, 0.0);

  x = 0.0, y = -10.0, z = 0.0;
  // Validate positive result
  result = func(x, y, z);
  EXPECT_GT(result, 0.0);


}

TEST(exercise11, algo_marcing_cubes_1) {
  // Load file example.json
  marching_cubes("example.json", "output1.off", -10, -10, 10, 10, -10, 10, 1);
}

TEST(exercise11, algo_marcing_cubes_2) {
  // Load file example.json
  marching_cubes("example2.json", "output2.off", -5, -5, 6, 6, -5, 6, 0.1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}