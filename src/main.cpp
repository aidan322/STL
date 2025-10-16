#include "CircularList.h"
#include <iostream>

int main() {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::cout << list << std::endl;

    return 0;
}
