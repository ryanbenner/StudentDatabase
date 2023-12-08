

#ifndef LISTNODE_H
#define LISTNODE_H
#include <cstdlib>
#include <iostream>

using namespace std;

template <typename T>
class ListNode {
    public:
        ListNode(T data);
        virtual ~ListNode();
        T m_data;
        ListNode<T>* m_next; // recursive data structure
        ListNode<T>* m_prev; // pointing to instances of itself

};

template <typename T>
ListNode<T>::ListNode(T data) {
    m_data = data;
    m_next = NULL;
    m_prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode() {
    m_next = NULL;
    m_prev = NULL;
}

#endif