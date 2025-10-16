#include "CircularList.h"
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    CircularList<int> list;
    assert(list.empty());
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    assert(list.size() == 3);
    assert(list.front() == 10);
    assert(list.back() == 30);

    // Iterator and range-for
    std::vector<int> v;
    for (auto &x : list) v.push_back(x);
    assert((v == std::vector<int>{10,20,30}));

    // pop_front
    list.pop_front();
    assert(list.front() == 20);
    assert(list.size() == 2);

    // pop_back
    list.pop_back();
    assert(list.back() == 20);
    assert(list.size() == 1);

    list.pop_back();
    assert(list.empty());

    std::cout << "All tests passed!\n";
    return 0;
}
