#pragma once

#include <unordered_map>

namespace LRUCache {

    template <typename T>
    class Node {
    public:
        Node(T aValue) : prev(nullptr), next(nullptr), theValue(aValue) {}

        ~Node() {
            prev = nullptr;
            next = nullptr;
        }

        Node(const Node& aCopy) {
            *this = aCopy;
        }

        Node& operator=(const Node& aNode) {
            theValue = aNode.theValue;
            prev = aNode.prev;
            next = aNode.next;

            return *this;
        }

        Node* prev;
        Node* next;
        T theValue;
    };

    template <typename T>
    class DoubleLinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        std::unordered_map<T, Node<T>*> cacheMap;

    public:
        DoubleLinkedList() : head(nullptr), tail(nullptr) {
            // Create dummy head and tail nodes
            head = new Node<T>(T());
            tail = new Node<T>(T());

            // Connect head and tail
            head->next = tail;
            tail->prev = head;
        }

        ~DoubleLinkedList() {
            Node<T>* current = head;

            while (current != nullptr) {
                Node<T>* next = current->next;
                delete current;
                current = next;
            }

            head = nullptr;
            tail = nullptr;
        }

        DoubleLinkedList(const DoubleLinkedList& aCopy) {
            *this = aCopy;
        }

        DoubleLinkedList& operator=(const DoubleLinkedList& aList) {
            Node<T>* current = head;

            // Clear list
            while (current != nullptr) {
                Node<T>* next = current->next;
                delete current;
                current = next;
            }

            head = nullptr;
            tail = nullptr;

            // Copy elements from aList
            current = aList.head;
            while (current != nullptr) {
                append(current->theValue);
                current = current->next;
            }

            return *this;
        }

        void prepend(T aValue) {
            Node<T>* temp = new Node<T>(aValue);

            if (nullptr == head) {
                head = temp;
                tail = temp;
            }

            else {
                temp->next = head;
                head->prev = temp;
                head = temp;
            }

            cacheMap[aValue] = temp;
        }

        void append(T aValue) {
            Node<T>* temp = new Node<T>(aValue);

            if (nullptr == head) {
                head = temp;
                tail = temp;
            }

            else {
                tail->next = temp;
                temp->prev = tail;
                tail = temp;
            }

            cacheMap[aValue] = temp;
        }

        void remove(T aValue) {
            auto iter = cacheMap.find(aValue);
            if (iter != cacheMap.end()) {
                Node<T>* nodeToRemove = iter->second;

                if (nodeToRemove == head) {
                    head = nodeToRemove->next;
                    if (nullptr != head) head->prev = nullptr;
                }
                else {
                    nodeToRemove->prev->next = nodeToRemove->next;
                    if (nullptr != nodeToRemove->next) nodeToRemove->next->prev = nodeToRemove->prev;
                }

                if (nodeToRemove == tail) {
                    tail = nodeToRemove->prev;
                    if (tail != nullptr) tail->next = nullptr;
                }

                delete nodeToRemove;
                cacheMap.erase(aValue);
            }
        }

        T popLRU() {
            T LRUvalue = head->next->theValue;
            remove(LRUvalue);

            return LRUvalue;
        }

        void update(T aValue) {
            remove(aValue);
            append(aValue);
        }

        size_t getLength() {
            return cacheMap.size();
        }
    };

}
