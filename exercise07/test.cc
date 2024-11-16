#include <gtest/gtest.h>
#include "solution.h"



TEST(exercise07, translation) {
  translate_mesh(
    "sample.off",
    {20,30,80},
    "sample_out.off");
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}