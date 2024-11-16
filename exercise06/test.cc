#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise06, rotate) {
  rotate_mesh_around_line(
    "sample.off",
    {{0, 0, 0}, {1, 2, 3}},
    20,
    "sample_out.off");
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}