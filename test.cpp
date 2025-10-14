#include "CircularList.h"
#include <cassert>
#include <iostream>

int main() {
    CircularList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    assert(list.front() == 10);
    assert(list.back() == 30);

    std::cout << "All tests passed!\n";
    return 0;
}
