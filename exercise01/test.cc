#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise01, cube_1) {
  cube_with_square_faces(0, 1, 0, 1, 0, 1, "cube_with_square_faces.ply");
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}