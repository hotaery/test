#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <binary_tree.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int rob(TreeNode* root) {
        return _robMyself(root);
    }

private:
    int _robMyself(TreeNode* root) {

    }
};

int main() {
    vector<int> val = {1, 4, 3, 2};
    auto root = data_structure::TreeNode<int>::createTree(val.begin(), val.end()); 
}