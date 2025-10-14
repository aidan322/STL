#include "CircularList.h"

int main() {
    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.print();

    return 0;
}
