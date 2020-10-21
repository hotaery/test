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
#include <single_list.h>
#include <output.h>
#include <numeric>
#include <stack>
#include <butil/endpoint.h>
#include <butil/containers/linked_list.h>
#include <regex>
#include <unistd.h>
#include <fcntl.h>
#include <bthread/unstable.h>
#include <bthread/bthread.h>
#include <assert.h>
#include <bthread/task_control.h>
#include <bthread/task_group.h>
#include <signal.h>
#include <sys/uio.h>
#include <butil/iobuf.h>
using namespace std;

#define ASSERT_EQ(a, b) assert((a) == (b))

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int v) : val(v), next(nullptr) {}
};
typedef data_structure::TreeNode<int> TreeNode;

template <typename C>
ListNode* createList(C&& c) {
    ListNode head(-1);
    ListNode* prev = &head;
    for (auto& v : c) {
        prev->next = new ListNode(v);
        prev = prev->next;
    }
    return head.next;
}

template <typename C>
ListNode* createCycleList(C&& c, int idx) {
    if (idx == -1) {
        return createList(c);
    }
    ListNode head(-1);
    ListNode* prev = &head;
    ListNode* cycle = nullptr;
    int i = 0;
    for (auto& v : c) {
        ListNode* curr = new ListNode(v);
        if (i == idx) {
            cycle = curr;
        }
        prev->next = curr;
        prev = prev->next;
        ++i;
    }
    if (cycle) {
        prev->next = cycle;
    }
    return head.next;
}

ostream& operator<<(ostream& os, ListNode* head) {
    while (head) {
        os << head->val;
        if (head->next) {
            os << "->";
        }
        head = head->next;
    }
    return os;
}

class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        return _isLongPressedName1(name, typed);
    }

private:
    bool _isLongPressedName1(const string& name, const string& typed) {
        int len1 = name.size();
        int len2 = typed.size();
        while (len1 > 0 && len2 > 0) {
            if (name[len1 - 1] != typed[len2 - 1]) {
                if (len2 < typed.size() && typed[len2 - 1] == typed[len2]) {
                    --len2;
                } else {
                    break;
                }
            } else {
                --len1;
                --len2;
            }
        }
        if (len2 > 0 && len2 < typed.size()) {
            for (int i = 0; i < len2; ++i) {
                if (typed[i] != typed[len2]) {
                    return false;
                }
            }
            return true;
        } 
        return len1 == 0 && len2 == 0;
    }
};

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    
}
