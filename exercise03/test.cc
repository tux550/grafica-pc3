#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise03, sphere_01) {
  sphere_with_quadrilateral_faces("sphere_with_quadrilateral_faces.ply", 5, 2, 3, 5);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}