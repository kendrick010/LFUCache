#include <iostream>
#include "DoubleLinkedList.h"

int main() {
    LRUCache::DoubleLinkedList<int> dll;
    dll.prepend(1);
    dll.prepend(2);
    dll.prepend(3);

    auto temp = dll.getRoot();
    temp = temp->next;
    dll.remove(temp);

    return 0;
}
