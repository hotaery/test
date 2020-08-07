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

    TreeNode(T&& v) : val(v), left(nullptr), right(nullptr) {}
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


    typename std::enable_if<std::is_integral<U>::value, U>::type operator()(T&& v, 
            typename std::enable_if<std::is_same<std::string, T>::value, int>::type = 0) {
        return std::stoi(v);
    }
};

template <typename T>
class BinaryTree {
public:
    BinaryTree() : node(nullptr) {}

    template <typename Iter>
    BinaryTree(Iter beg, Iter end) : node(nullptr) {
        typedef typename std::decay<decltype(*beg)>::type U;
        if (beg == end) {
            return;
        }
        if (TreeNodeIsNull<U>()(*beg)) {
            return;
        }
        TreeNode<T>* root = new TreeNode<T>(TypeTransform<U, T>()(*beg));
        node = root;
        std::queue<TreeNode<T>*> q;
        q.push(root);
        ++beg;
        while (beg != end) {
            TreeNode<T>* curr = q.front();
            q.pop();
            if (TreeNodeIsNull<U>()(*beg)) {
                curr->left = nullptr;
            } else {
                curr->left = new TreeNode<T>(TypeTransform<U, T>()(*beg));
                q.push(curr->left);
            }
            ++beg;
            if (TreeNodeIsNull<U>()(*beg)) {
                curr->right = nullptr;
            } else {
                curr->right = new TreeNode<T>(TypeTransform<U, T>()(*beg));
                q.push(curr->right);
            }
            ++beg;
        }
    }

    ~BinaryTree() {
        _destroy(root);
    }

    std::string describe() const {

    }

    TreeNode<T>* handle() const {
        return node;
    }

private:
    static void _destroy(TreeNode<T>* root) {
        if (!root) {
            return;
        }
        _destroy(root->left);
        _destroy(root->right);
        delete root;
    }

private:
    TreeNode<T>* node;
};

} // namespace data_structure

#endif // DATA_STRUCTURE_BINARY_TREE_H