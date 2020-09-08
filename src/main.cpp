#include <iostream>
#include <atomic>
#include <array>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <thread>
#include <stdarg.h>
#include <binary_tree.h>
#include <output.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        if (n < k) {
            return {};
        }
        return _combine3(n, k);
    }

private:
    vector<vector<int>> _ret;
    vector<int> _curr;

    vector<vector<int>> _combine1(int n, int k) {
        _dfs(1, n, k);
        return _ret;
    }

    void _dfs(int left, int right, int k) {
        if (k == 0) {
            _ret.push_back(_curr);
            return;
        } 
        if (right - left + 1 < k) {
            return;
        }
        _curr.push_back(left);
        _dfs(left + 1, right, k - 1);
        _curr.pop_back();
        _dfs(left + 1, right, k);
    } 

private:
    //0011 -> 0101 -> 0110 -> 1001 -> 1010 -> 1100
    vector<vector<int>> _combine2(int n, int k) {
        vector<vector<int>> ret;
        vector<int> mask(n, 0);
        fill(mask.begin(), mask.begin() + k, 1);
        while (true) {
            vector<int> v;
            for (int i = 0; i < n; ++i) {
                if (mask[i]) {
                    v.push_back(i + 1);
                }
            }
            ret.push_back(move(v));
            int idx = 0;
            for (; idx < n && !mask[idx]; ++idx) {
            }
            int one_start = idx;
            for (; idx < n && mask[idx]; ++idx) {
            }
            int one_end = idx;
            if (idx == n) {
                break;
            }
            mask[idx] = 1;
            fill(mask.begin() + one_start, mask.begin() + one_end, 0);
            fill(mask.begin(), mask.begin() + (one_end - one_start - 1), 1);
        }
        return ret;
    }

private:
    vector<vector<int>> _combine3(int n, int k) {
        vector<int> v(k, 0);
        for (int i = 0; i < k; ++i) {
            v[i] = i + 1;
        }
        vector<vector<int>> ret;
        while (true) {
            ret.push_back(v);
            if (v.back() == n && v.back() - v.front() == k - 1) {
                break;
            }
            int idx = 1;
            while (idx < k && v[idx] == v[idx - 1] + 1) {
                ++idx;
            }
            v[idx - 1] += 1;
            for (int i = 0; i < idx - 1; ++i) {
                v[i] = i + 1;
            }
        }
        return ret;
    }
};

int main() {
    {
        auto ret = Solution().combine(4, 2);
        utils::operator<<(cout, ret) << endl;
    }
}