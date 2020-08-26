#ifndef DATA_STRUCTURE_SINGLE_LIST_H
#define DATA_STRUCTURE_SINGLE_LIST_H

namespace data_structure {

struct ListNodeBase {
    ListNodeBase* next;

    ListNodeBase() : next(nullptr) {}
};

class SingleListBase {
public:
    SingleListBase();


private:
    ListNodeBase* _head;
};

template <typename T>
struct ListNode : public ListNodeBase {
    T val;

    ListNode(T v) : val(v), ListNodeBase() {}
};

} // namespace data_structure

#endif 