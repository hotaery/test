#include <iostream>
#include <atomic>
#include <array>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string.h>
#include <bthread/bthread.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bthread/task_control.h>
#include <bthread/task_group.h>
#include <bthread/task_meta.h>
#include <chrono>
#include <thread>
#include <stdarg.h>
#include <binary_tree.h>
using namespace std;

typedef data_structure::TreeNode<int> TreeNode;

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        _dfs(root);
        return ret;
    }

private:
    vector<string> ret;
    vector<int> path;

    void _path2str(int last) {
        string str;
        str.reserve(path.size() * 3);
        for (int i = 0; i < path.size(); ++i) {
            str.append(to_string(path[i]));
            str.append("->");
        }
        str.append(to_string(last));
        ret.emplace_back(move(str));
    }

    void _dfs(TreeNode* node) {
        if (!node) {
            return;
        }
        if (!node->left && !node->right) {
            _path2str(node->val);
            return;
        }
        path.push_back(node->val);
        _dfs(node->left);
        _dfs(node->right);
        path.pop_back();
    }
};

int main() {
    vector<string> v{"1", "2", "3", "null", "5"};
    data_structure::BinaryTree<int> tree(v.begin(), v.end());
    auto ret = Solution().binaryTreePaths(tree.handle());
    for (auto& path : ret) {
        cout << path << '\n';
    }
    cout << endl;
}