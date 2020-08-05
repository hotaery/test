#ifndef DATA_STRUCTURE_BINARY_TREE_H
#define DATA_STRUCTURE_BINARY_TREE_H

#include <iostream>
#include <queue>
#include <string>
#include <cmath>

namespace data_structure {

template <typename T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}

    template <typename Iter, typename Fn, typename Gn> 
    static TreeNode* createTree(Iter beg, Iter end, Fn is_null, Gn to_node) {
        if (beg == end) {
            return nullptr;
        }
        if (is_null(*beg)) {
            return nullptr;
        }
        
        TreeNode* root = to_node(*beg);
        std::queue<TreeNode> q;
        q.push(root);
        ++beg;
        while (beg != end) {
            TreeNode* prev = q.front();
            q.pop();
            if (is_null(*beg)) {
                prev->left = nullptr;
            } else {
                prev->left = to_node(*beg);
                q.push(prev->left);
            }
            ++beg;
            if (beg == end) {
                break;
            }
            if (is_null(*beg)) {
                prev->right = nullptr;
            } else {
                prev->right = to_node(*beg);
                q.push(prev->right);
            }
            ++beg;
        }
        return root;
    }

    template <typename Fn>
    static void destroyTree(TreeNode* root, Fn dtor) {
        if (!root) {
            return;
        }
        destroyTree(root->left);
        destroyTree(root->right);
        dtor(root);
    }

    /**
     *                 8
     *         ________|________
     *        |                 |
     *        7                 9
     *    ____|____         ____|____
     *   |         |       |         |
     *   3         4       10        11
     * __|__     __|__   __|__     __|__
     *|     |   |     | |     |   |     |
     *1     2   5     6 12    13  15    17
     */
    template <typename Fn>
    static std::string describe(TreeNode* root, Fn to_str) {
        return "";
    }

    static int depth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int left_depth = depth(root->left);
        int right_depth = depth(root->right);
        return std::max(left_depth, right_depth) + 1;
    }
};

template <typename T>
struct ToStr {
    std::string operator()(TreeNode<T>* node) {
        return std::to_string(node->val);
    }
};

} // namespace data_structure

template <typename T>
std::ostream& operator<<(std::ostream& os, data_structure::TreeNode<T>* root) {
    os << data_structure::TreeNode<T>::describe(root, ToStr<T>());
    return os;
}

#endif // DATA_STRUCTURE_BINARY_TREE_H