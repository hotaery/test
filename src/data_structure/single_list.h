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

template <typename T>
class SigleList : public SingleListBase {

};

} // namespace data_structure

#endif // DATA_STRUCTURE_SINGLE_LIST_H