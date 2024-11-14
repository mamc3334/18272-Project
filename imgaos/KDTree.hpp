#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>
#include <memory>
#include <cmath>
#include <unordered_map>
#include "aosinfrequentcolor.hpp"

class KDTree {
public:
    KDTree(const std::vector<color>& colors);
    color nearestNeighbor(const color& target) const;

private:
    struct Node {
        color point;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node(const color& pt) : point(pt), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> buildTree(std::vector<color>& colors, int depth);
    color nearestNeighborSearch(const color& target, Node* node, int depth, color best, double bestDist) const;
    double colorDistance(const color& c1, const color& c2) const;

    std::unique_ptr<Node> root;
};

#endif // KDTREE_HPP
