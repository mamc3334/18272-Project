#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>
#include <memory>
#include <cmath>
#include <unordered_map>
#include "aosinfrequentcolor.hpp"

// KDTree for smallColor
class KDTreeSmallColor {
public:
    KDTreeSmallColor(const std::vector<smallColor>& colors);
    [[nodiscard]] smallColor nearestNeighbor(const smallColor& target) const;

private:
    struct Node {
        smallColor point;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(const smallColor& point) : point(point), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> buildTree(std::vector<smallColor>& colors, int depth);
    smallColor nearestNeighborSearch(const smallColor& target, Node* node, int depth, smallColor best, double bestDist) const;
    [[nodiscard]] double colorDistance(const smallColor& color1, const smallColor& color2) const;

    std::unique_ptr<Node> root;
};

// KDTree for bigColor
class KDTreeBigColor {
public:
    KDTreeBigColor(const std::vector<bigColor>& colors);
    [[nodiscard]] bigColor nearestNeighbor(const bigColor& target) const;

private:
    struct Node {
        bigColor point;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(const bigColor& point) : point(point), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> buildTree(std::vector<bigColor>& colors, int depth);
    bigColor nearestNeighborSearch(const bigColor& target, Node* node, int depth, bigColor best, double bestDist) const;
    [[nodiscard]] double colorDistance(const bigColor& color1, const bigColor& color2) const;

    std::unique_ptr<Node> root;
};

#endif // KDTREE_HPP
