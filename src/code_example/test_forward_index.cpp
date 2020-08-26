#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

const char INVALID = 'N';
const int LENGTH = 10;
vector<char> g_vec(LENGTH, INVALID);
vector<char> g_tmp;
int curr_index = 0;

void forwardIndex() {
    curr_index += 1;
    curr_index %= LENGTH;
}

void addOneElem(char c) {
    char* saved[4];
    for (int i = 0; i < 4; ++i) {
        char* curr = &g_vec[curr_index];
        forwardIndex();
        if (*curr == INVALID) {
            *curr = c;
            return;
        }
        saved[i] = curr;
    }

    vector<char> tmp(LENGTH, INVALID);
    copy(g_vec.begin() + curr_index, g_vec.end(), tmp.begin());    
    fill(g_vec.begin() + curr_index, g_vec.end(), INVALID);
    g_tmp = move(tmp);
    g_vec[curr_index] = *saved[2];
    *saved[2] = *saved[1];
    *saved[1] = INVALID;
    forwardIndex();
    forwardIndex();
    g_vec[curr_index] = *saved[3];
    *saved[3] = INVALID;
    forwardIndex();
    g_vec[curr_index] = c;
    forwardIndex();
}

void init() {
    g_vec[0] = '0';
    g_vec[1] = '1';
    g_vec[2] = '2';
    g_vec[3] = '3';
}

void print() {
    cout << "g_vec: ";
    copy(g_vec.begin(), g_vec.end(), ostream_iterator<char>(cout, ", "));
    cout << '\n';
    cout << "g_tmp: ";
    copy(g_tmp.begin(), g_tmp.end(), ostream_iterator<char>(cout, ", "));
    cout << '\n';
    cout << "curr_index: " << curr_index << '\n';
    cout << "********************" << endl;;
}

int main() {
    init();
    print();
    addOneElem('4');
    print();
}
