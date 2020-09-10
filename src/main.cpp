#include <vector>
#include <unordered_set>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        return _combinationSum2(candidates, target); 
    }

private:
    vector<vector<int>> _ret;
    vector<int> _curr;
    vector<int>* _candidates;

    vector<vector<int>> _combinationSum2(vector<int>& candidates, int target) {
        _candidates = &candidates;
        _dfs(0, target);
        return _ret;
    }

    void _dfs(int idx, int target) {
        if (target < 0) {
            return;
        }
        if (target == 0) {
            _ret.push_back(_curr);
            return;
        }
        if (idx > _candidates->size()) {
            return;
        }

        _curr.push_back(_candidates->at(idx));
        _dfs(idx + 1, target - _candidates->at(idx));
        _curr.pop_back();
        _dfs(idx + 1, target);
    }
};

int main() {

}