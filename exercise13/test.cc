#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise13, algo_painter_algorithm_textures) {
  painter_algorithm_textures(
    "sample.ply",
    "sample.png",
    "output.png",
    -0.5, -0.5, 0.5, 0.5,
    400, 400
  );
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}