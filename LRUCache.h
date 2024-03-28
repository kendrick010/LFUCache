#pragma once

#include <string>
#include <optional>
#include "DoubleLinkedList.h"

namespace LRUCache {

    template <typename T, size_t maxSize>
    class LRUCache {
    private:
        size_t LFUcount;

        std::unordered_map<std::string, T> valueMap;
        std::unordered_map<std::string, size_t> freqMap;
        std::unordered_map<size_t, DoubleLinkedList<std::string>> dllMap;

        void updateFreq(std::string aKey) {
            // Get current count, else default value of zero
            auto freq = freqMap[aKey];
            freqMap[aKey] += 1;

            dllMap[freq].popLRU();
            dllMap[freq + 1].popLRU();

            if (freq == LFUcount && 0 == dllMap[freq].getLength()) LFUcount += 1;
        }

    public:
        LRUCache() : LFUcount(1) {}

        ~LRUCache() = default;

        LRUCache(const LRUCache& aCopy) {
            *this = aCopy;
        }

        LRUCache& operator=(const LRUCache& aCache) {
            LFUcount = aCache.theValue;
            valueMap = aCache.valueMap;
            freqMap = aCache.freqMap;
            dllMap = aCache.dllMap;

            return *this;
        }

        void put(std::string aKey, T aValue) {
            if (0 == maxSize) return;

            auto iter = valueMap.find(aKey);
            if (iter == valueMap.end() && maxSize == valueMap.size()) {
                auto LFUkey = dllMap[LFUcount].popLRU();

                valueMap.erase(LFUkey);
                freqMap.erase(LFUkey);
            }

            valueMap[aKey] = aValue;
            updateFreq(aKey);
        }

        std::optional<T> get(std::string aKey) {
            auto iter = valueMap.find(aKey);
            if (iter == valueMap.end()) {
                return std::nullopt;
            }

            updateFreq(aKey);

            return valueMap[aKey];
        }
    };

}