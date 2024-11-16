#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise03, sphere_02) {
  sphere_with_texture(
    "sample.ply",
    "sample.png",
    {2, 3, 5},
    "sample_out.ply");
    
}

TEST(exercise03, sphere_03) {
  sphere_with_texture(
    "sample2.ply",
    "sample.png",
    {0, 1, 10},
    "sample2_out.ply");
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}