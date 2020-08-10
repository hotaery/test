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
struct TreeNodeIsNull<std::string&> {
    bool operator()(const std::string& s) const {
        return s == "null";
    }
};

struct TypeTtoTypeU {
    template <typename T, typename U>
    typename std::enable_if<
        std::is_constructible<U, T>::value,
    U>::type operator()(T&& v) {
        return U(v);
    }

    template <typename T, typename U>
    typename std::enable_if<std::is_integral<U>::value, U>::type operator()(T&& v,
        typename std::enable_if<
            std::is_same<
                typename std::remove_reference<
                    typename std::remove_cv<T>::type
                >::type, 
                std::string
            >::value
        >::type* = 0) {
        return std::stoi(v);
    }
};

template <typename T>
class BinaryTree {
public:
    BinaryTree() : node(nullptr) {}

    template <typename Iter>
    BinaryTree(Iter beg, Iter end) : node(nullptr) {
        typedef decltype(*beg) U;
        if (beg == end) {
            return;
        }
        if (TreeNodeIsNull<U>()(*beg)) {
            return;
        }
        TreeNode<T>* root = new TreeNode<T>(TypeTtoTypeU().operator()<U, T>(*beg));
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
                curr->left = new TreeNode<T>(TypeTtoTypeU().operator()<U, T>(*beg));
                q.push(curr->left);
            }
            ++beg;
            if (beg == end) {
                break;
            }
            if (TreeNodeIsNull<U>()(*beg)) {
                curr->right = nullptr;
            } else {
                curr->right = new TreeNode<T>(TypeTtoTypeU().operator()<U, T>(*beg));
                q.push(curr->right);
            }
            ++beg;
        }
    }

    ~BinaryTree() {
        _destroy(node);
    }

    std::string describe() const {
        return "";
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