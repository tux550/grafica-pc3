#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise13, algo_painter_algorithm_textures) {
  painter_algorithm_textures(
    "sample.ply",
    "sample.png",
    "output.png",
    -1, -1, 1, 1,
    800, 1200
  );
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}