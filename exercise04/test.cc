#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise03, sphere_02) {
  sphere_with_triangular_faces("sphere_with_triangular_faces.ply", 5, 2, 3, 5);
}

TEST(exercise03, sphere_03) {
  sphere_with_triangular_faces("low_res.ply", 2, 0, 1, 10, 10);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}