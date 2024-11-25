#include "KDTree.hpp"
#include <limits>
#include <algorithm>

//KDTreeSmallColor Implementation

KDTreeSmallColor::KDTreeSmallColor(const std::vector<smallColor>& colors) {
    std::vector<smallColor> colorsCopy = colors;
    root = buildTree(colorsCopy, 0);
}

std::unique_ptr<KDTreeSmallColor::Node> KDTreeSmallColor::buildTree(std::vector<smallColor>& colors, int depth) {
    if (colors.empty()) {return nullptr;}

    int const axis = depth % 3;
    std::sort(colors.begin(), colors.end(), [axis](const smallColor& one, const smallColor& two) {
        if (axis == 0){ return one.r < two.r;}
        if (axis == 1){ return one.g < two.g;}
        return one.b < two.b;
    });

    size_t const medianIndex = colors.size() / 2;
    auto node = std::make_unique<Node>(colors[medianIndex]);

    auto leftColors = std::vector<smallColor>(colors.begin(), colors.begin() + static_cast<std::vector<smallColor>::difference_type>(medianIndex));
    auto rightColors = std::vector<smallColor>(colors.begin() + static_cast<std::vector<smallColor>::difference_type>(medianIndex) + 1, colors.end());

    node->left = buildTree(leftColors, depth + 1);
    node->right = buildTree(rightColors, depth + 1);

    return node;
}

smallColor KDTreeSmallColor::nearestNeighbor(const smallColor& target) const {
    return nearestNeighborSearch(target, root.get(), 0, root->point, colorDistance(target, root->point));
}

smallColor KDTreeSmallColor::nearestNeighborSearch(const smallColor& target, Node* node, int depth, smallColor best, double bestDist) const {
    if (node == nullptr){ return best;}

    double const dist = colorDistance(target, node->point);
    if (dist < bestDist) {
        bestDist = dist;
        best = node->point;
    }

    int const axis = depth % 3;
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

double KDTreeSmallColor::colorDistance(const smallColor& color1, const smallColor& color2) const {
    return ((color1.r - color2.r) * (color1.r - color2.r)) + ((color1.g - color2.g) * (color1.g - color2.g)) + ((color1.b - color2.b) * (color1.b - color2.b));
}

//KDTreeBigColor Implementation

KDTreeBigColor::KDTreeBigColor(const std::vector<bigColor>& colors) {
    std::vector<bigColor> colorsCopy = colors;
    root = buildTree(colorsCopy, 0);
}

std::unique_ptr<KDTreeBigColor::Node> KDTreeBigColor::buildTree(std::vector<bigColor>& colors, int depth) {
    if (colors.empty()){ return nullptr;}

    int const axis = depth % 3;
    std::sort(colors.begin(), colors.end(), [axis](const bigColor& one, const bigColor& two) {
        if (axis == 0){ return one.r < two.r;}
        if (axis == 1){ return one.g < two.g;}
        return one.b < two.b;
    });

    size_t const medianIndex = colors.size() / 2;
    auto node = std::make_unique<Node>(colors[medianIndex]);

    auto leftColors = std::vector<bigColor>(colors.begin(), colors.begin() + static_cast<std::vector<bigColor>::difference_type>(medianIndex));
    auto rightColors = std::vector<bigColor>(colors.begin() + static_cast<std::vector<bigColor>::difference_type>(medianIndex) + 1, colors.end());

    node->left = buildTree(leftColors, depth + 1);
    node->right = buildTree(rightColors, depth + 1);

    return node;
}

bigColor KDTreeBigColor::nearestNeighbor(const bigColor& target) const {
    return nearestNeighborSearch(target, root.get(), 0, root->point, colorDistance(target, root->point));
}

bigColor KDTreeBigColor::nearestNeighborSearch(const bigColor& target, Node* node, int depth, bigColor best, double bestDist) const {
    if (node == nullptr){ return best;}

    double const dist = colorDistance(target, node->point);
    if (dist < bestDist) {
        bestDist = dist;
        best = node->point;
    }

    int const axis = depth % 3;
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

double KDTreeBigColor::colorDistance(const bigColor& color1, const bigColor& color2) const {
    return ((color1.r - color2.r) * (color1.r - color2.r)) + ((color1.g - color2.g) * (color1.g - color2.g)) + ((color1.b - color2.b) * (color1.b - color2.b));
}
