#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise02, cube_1) {
  cube_with_triangular_faces(0, 1, 0, 1, 0, 1, "cube_with_triangular_faces.ply");
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}