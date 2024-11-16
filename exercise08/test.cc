#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise08, algo_catmull_clark) {
  catmull_clark("sample.ply",5,"sample_out.ply");
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}