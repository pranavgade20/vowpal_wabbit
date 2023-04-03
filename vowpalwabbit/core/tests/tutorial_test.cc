// Copyright (c) by respective owners including Yahoo!, Microsoft, and
// individual contributors. All rights reserved. Released under a BSD (revised)
// license as described in the file LICENSE.

#include "simulator.h"

#include <gtest/gtest.h>
#include <fstream>

TEST(Tutorial, CppSimulatorWithoutInteraction)
{
  auto ctr = simulator::_test_helper(
      std::vector<std::string>{"--cb_explore_adf", "--quiet", "--epsilon=0.2", "--random_seed=5"});
  EXPECT_GT(ctr.back(), 0.37f);
  EXPECT_LT(ctr.back(), 0.49f);
}

TEST(Tutorial, CppSimulatorWithoutInteractionToLogfile)
{
  auto ctr = simulator::_test_helper(
      std::vector<std::string>{"--cb_explore_adf", "--quiet", "--epsilon=0.2", "--random_seed=5"});
  std::ifstream logfile("log.csv");
  std::string s1;
  logfile >> s1;
  EXPECT_PRED2([](std::string s1, std::string s2) {
        return s1 == s2;}, s1, "i,user,time_of_day,chosen_action,prob,cost");
  // more tests can be written to verify the datatype of the csv contents and so on
}

TEST(Tutorial, CppSimulatorWithInteraction)
{
  auto ctr = simulator::_test_helper(
      std::vector<std::string>{"--cb_explore_adf", "--quadratic=UA", "--quiet", "--epsilon=0.2", "--random_seed=5"});
  float without_save = ctr.back();
  EXPECT_GT(without_save, 0.7f);

  ctr = simulator::_test_helper_save_load(
      std::vector<std::string>{"--cb_explore_adf", "--quadratic=UA", "--quiet", "--epsilon=0.2", "--random_seed=5"});
  float with_save = ctr.back();
  EXPECT_GT(with_save, 0.7f);

  EXPECT_FLOAT_EQ(without_save, with_save);
}