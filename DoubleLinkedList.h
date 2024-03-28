#pragma once

#include <cstddef>

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
    public:
        DoubleLinkedList() : root(nullptr) {}

        ~DoubleLinkedList() {
            Node<T>* temp{root};

            while (nullptr != temp) {
                Node<T>* next{temp->next};
                delete temp;
                temp = next;
            }

            root = nullptr;
        }

        DoubleLinkedList(const DoubleLinkedList& aCopy) {
            *this = aCopy;
        }

        DoubleLinkedList& operator=(const DoubleLinkedList& aList) {
            root = aList.root;
            size = aList.size;

            return *this;
        }

        void prepend(T aValue) {
            auto temp = new Node<T>(aValue);

            if (nullptr == root) root = temp;
            else {
                temp->next = root;
                root->prev = temp;
                root = temp;
            }

            ++size;
        }

        void remove(Node<T>* aNode) {
            if (nullptr == aNode) return;

            if (root == aNode) {
                root = aNode->next;
                if (nullptr != root) root->prev = nullptr;
            }
            else {
                aNode->prev->next = aNode->next;
                if (nullptr != aNode->next) aNode->next->prev = aNode->prev;
            }

            delete aNode;
            --size;
        }

        Node<T>* getRoot() {
            return root;
        }

        size_t getSize() {
            return size;
        }

        void setRoot(Node<T>* aNode) {
            root = aNode;
        }

    private:
        Node<T>* root;
        size_t size{0};
    };

}