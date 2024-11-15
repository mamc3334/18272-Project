#include "../imgaos/aosinfrequentcolor.hpp"
#include "../imgaos/KDTree.hpp"
#include "common/binaryio.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <random>
#include <gtest/gtest.h>
#include <cmath>
// Define the `smallColor` structure for the tests

// Test for tree construction with non-empty input
/*
TEST(KDTreeSmallColorTest, ConstructionNonEmpty) {
    std::vector<smallColor> colors = {
        {1, 2, 3},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    KDTreeSmallColor tree(colors);
    ASSERT_NO_THROW(tree.nearestNeighbor({0.0, 0.0, 0.0}));
}

// Test for nearest neighbor
TEST(KDTreeSmallColorTest, NearestNeighbor) {
    std::vector<smallColor> colors = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0},
        {10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0}
    };
    KDTreeSmallColor tree(colors);

    // Query a point close to {1.0, 2.0, 3.0}
    smallColor query = {1.1, 2.1, 3.1};
    smallColor expected = {1.0, 2.0, 3.0};
    ASSERT_EQ(tree.nearestNeighbor(query), expected);

    // Query a point close to {13.0, 14.0, 15.0}
    query = {12.9, 13.9, 14.9};
    expected = {13.0, 14.0, 15.0};
    ASSERT_EQ(tree.nearestNeighbor(query), expected);
}

// Test for empty input
TEST(KDTreeSmallColorTest, EmptyInput) {
    std::vector<smallColor> emptyColors;
    ASSERT_NO_THROW({
        KDTreeSmallColor tree(emptyColors);
        smallColor query = {1.0, 1.0, 1.0};
        // Ensure no crash but verify behavior (depends on implementation)
        EXPECT_ANY_THROW(tree.nearestNeighbor(query));
    });
}

// Test for boundary conditions
TEST(KDTreeSmallColorTest, BoundaryConditions) {
    std::vector<smallColor> colors = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0},
        {10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0}
    };
    KDTreeSmallColor tree(colors);

    // Query a point far from all data points
    smallColor query = {-100.0, -100.0, -100.0};
    smallColor expected = {1.0, 2.0, 3.0};  // Closest in this case
    ASSERT_EQ(tree.nearestNeighbor(query), expected);

    query = {100.0, 100.0, 100.0};
    expected = {13.0, 14.0, 15.0};
    ASSERT_EQ(tree.nearestNeighbor(query), expected);
}

// Test for duplicate points in input
TEST(KDTreeSmallColorTest, DuplicatePoints) {
    std::vector<smallColor> duplicates = {
        {1.0, 2.0, 3.0},
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };
    KDTreeSmallColor tree(duplicates);

    smallColor query = {1.1, 2.1, 3.1};
    smallColor expected = {1.0, 2.0, 3.0};  // Should handle duplicates gracefully
    ASSERT_EQ(tree.nearestNeighbor(query), expected);
}
*/