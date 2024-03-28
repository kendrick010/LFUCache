#include <iostream>
#include "LRUCache.h"

int main() {
    LRUCache::LRUCache<int, 2> lfu;

    lfu.put("a", 1);
    std::cout << "Inserted a: 1" << std::endl;
    lfu.put("b", 2);
    std::cout << "Inserted b: 2" << std::endl;
    auto result1 = lfu.get("a");
    std::cout << "Retrieved a: " << (result1 ? std::to_string(*result1) : "Not found") << std::endl;

    lfu.put("c", 3);
    std::cout << "Inserted c: 3" << std::endl;
    auto result2 = lfu.get("b");
    std::cout << "Retrieved b: " << (result2 ? std::to_string(*result2) : "Not found") << std::endl;
    auto result3 = lfu.get("c");
    std::cout << "Retrieved c: " << (result3 ? std::to_string(*result3) : "Not found") << std::endl;

    lfu.put("d", 4);
    std::cout << "Inserted d: 4" << std::endl;

    auto result4 = lfu.get("a");
    std::cout << "Retrieved a: " << (result4 ? std::to_string(*result4) : "Not found") << std::endl;
    auto result5 = lfu.get("c");
    std::cout << "Retrieved c: " << (result5 ? std::to_string(*result5) : "Not found") << std::endl;
    auto result6 = lfu.get("d");
    std::cout << "Retrieved d: " << (result6 ? std::to_string(*result6) : "Not found") << std::endl;

    return 0;
}
