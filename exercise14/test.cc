#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise14, sphere_rotation) {
  frames_of_a_textured_sphere_rotating(
    "sample.ply",
    "sample.png",
    // Rotate around the z-axis
    //0, 0, 0,
    //0, 0, 1, 
    // Rotate around self
    0, 1, 10,
    0, 1, 0,
    "frames/frame"
  );
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}