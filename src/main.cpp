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
#include <chrono>
#include <thread>
#include <stdarg.h>
#include <binary_tree.h>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        return _getPermutation(n, k); 
    }

private:
    typedef vector<int>::iterator Iter;
    vector<int> _permutatian;
    vector<int> _fac;

    string _getPermutation(int n, int k) {
        if (n == 0) {
            return "";
        }
        _init(n);
        string ret;
        ret.reserve(n);
        if (k >= _fac.back()) {
            reverse(_permutatian.begin(), _permutatian.end());
        } else {
            _getSubPermutation(_permutatian.begin(), _permutatian.end(), k);
        }
        transform(_permutatian.begin(), _permutatian.end(), back_inserter(ret), [](int v) {
            return '0' + v;
        });
        return ret;
    }

    void _init(int n) {
        _permutatian.resize(n);
        _fac.resize(n);
        _permutatian[0] = 1;
        _fac[0] = 1;
        for (int i = 1; i < n; ++i) {
            _permutatian[i] = _permutatian[i - 1] + 1;
            _fac[i] = (i + 1) * _fac[i - 1];
        }
    }

    void _getSubPermutation(Iter beg, Iter end, int k) {
        if (k <= 1) {
            return;
        }
        int n = distance(beg, end);
        n -= 1;
        if (k <= _fac[n - 1]) {
            return _getSubPermutation(beg + 1, end, k);
        } 
        int idx = k / _fac[n - 1];
        if (k % _fac[n - 1] == 0) {
            --idx;
        }
        swap(*beg, *(beg + idx));
        sort(beg + 1, end);
        return _getSubPermutation(beg + 1, end, k - idx * _fac[n - 1]);
    }
};

int main() {
    cout << Solution().getPermutation(3, 5) << endl;
}