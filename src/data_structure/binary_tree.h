#ifndef DATA_STRUCTURE_BINARY_TREE_H
#define DATA_STRUCTURE_BINARY_TREE_H

#include <iostream>
#include <queue>
#include <string>
#include <cmath>
#include <type_traits>

namespace data_structure {

template <typename T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T&& v) : val(v), TreeNodeBase() {}
};

template <typename T>
struct TreeNodeIsNull {
    bool operator()(T&&) const {
        return false;
    }
};

template <>
struct TreeNodeIsNull<std::string> {
    bool operator()(const std::string& s) const {
        return s == "null";
    }
};

template <typename T, typename U>
struct TypeTransform {
    U operator()(T&& v) {
        return v;
    }

    U operator()(T&& v, std::enable_if_t<std::is_same_v<T, std::string>, int> = 0, 
                std::enable_if_t<std::integral_v<U>, int> = 0) {
        return std::stoi(v);
    }
};

template <typename T>
class BinaryTree {
public:
    BinaryTree() : node(nullptr) {}

    template <typename Iter>
    BinaryTree(Iter beg, Iter end) {

    }

    ~BinaryTree();

    std::string describe() const;

    TreeNode* handle() const {
        return node;
    }

private:
    void _destroy();

private:
    TreeNode* node;
};

} // namespace data_structure

#endif // DATA_STRUCTURE_BINARY_TREE_H