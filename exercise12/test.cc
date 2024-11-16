#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise12, algo_painter_basic) {
  painter_algorithm_simple_cosine_illumination(
    "sample.ply",
    "output.ppm",
    -1, -1, 1, 1,
    800, 1200
  );
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}