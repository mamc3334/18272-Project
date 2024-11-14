#include "KDTree.hpp"
#include <limits>
#include <algorithm>

KDTree::KDTree(const std::vector<color>& colors) {
    std::vector<color> colorsCopy = colors;
    root = buildTree(colorsCopy, 0);
}

std::unique_ptr<KDTree::Node> KDTree::buildTree(std::vector<color>& colors, int depth) {
    if (colors.empty()) return nullptr;

    int axis = depth % 3;  // Cycles through r, g, b axes
    std::sort(colors.begin(), colors.end(), [axis](const color& a, const color& b) {
        if (axis == 0) return a.r < b.r;
        if (axis == 1) return a.g < b.g;
        return a.b < b.b;
    });

    size_t medianIndex = colors.size() / 2;
    auto node = std::make_unique<Node>(colors[medianIndex]);

    // Convert medianIndex to the correct signed type for iterator arithmetic
    auto leftColors = std::vector<color>(colors.begin(), colors.begin() + static_cast<std::vector<color>::difference_type>(medianIndex));
    auto rightColors = std::vector<color>(colors.begin() + static_cast<std::vector<color>::difference_type>(medianIndex) + 1, colors.end());

    node->left = buildTree(leftColors, depth + 1);
    node->right = buildTree(rightColors, depth + 1);

    return node;
}

color KDTree::nearestNeighbor(const color& target) const {
    return nearestNeighborSearch(target, root.get(), 0, root->point, colorDistance(target, root->point));
}

color KDTree::nearestNeighborSearch(const color& target, Node* node, int depth, color best, double bestDist) const {
    if (!node) return best;

    double d = colorDistance(target, node->point);
    if (d < bestDist) {
        bestDist = d;
        best = node->point;
    }

    int axis = depth % 3;
    Node* next = (axis == 0 && target.r < node->point.r) || (axis == 1 && target.g < node->point.g) || (axis == 2 && target.b < node->point.b)
                   ? node->left.get() : node->right.get();
    Node* other = next == node->left.get() ? node->right.get() : node->left.get();

    best = nearestNeighborSearch(target, next, depth + 1, best, bestDist);
    bestDist = colorDistance(target, best);

    if (std::abs((axis == 0 ? target.r - node->point.r : axis == 1 ? target.g - node->point.g : target.b - node->point.b)) < std::sqrt(bestDist)) {
        best = nearestNeighborSearch(target, other, depth + 1, best, bestDist);
    }

    return best;
}

double KDTree::colorDistance(const color& c1, const color& c2) const {
    return (c1.r - c2.r) * (c1.r - c2.r) + (c1.g - c2.g) * (c1.g - c2.g) + (c1.b - c2.b) * (c1.b - c2.b);
}