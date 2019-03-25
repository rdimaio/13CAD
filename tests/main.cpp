/**
 * @file main.cpp
 * @brief Main file for the unit tests, runs all the unit tests together
 * @author Riccardo Di Maio
 * @version 1.0 10/12/18
 */

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}