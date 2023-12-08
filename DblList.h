

#ifndef DBLLIST_H
#define DBLLIST_H

#include "ListNode.h"

template <typename T>
class DblList {
    public:
        DblList();
        virtual ~DblList();
        void addFront(T data);
        void addBack(T data);
        void add(int pos, T data);
        T removeFront();
        T removeBack();
        T remove(int pos);
        void removeData(T data);
        bool isEmpty();
        int getSize();
        T get(int pos);

        template <typename S>
        friend class PQueue;

    private:
        ListNode<T>* m_front;
        ListNode<T>* m_back;
        int m_size;
};

template<typename T>
DblList<T>::DblList() {
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template<typename T>
DblList<T>::~DblList() {
    // loop through list and delete all nodes
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template <typename T>
void DblList<T>::removeData(T data) {
    // fill out here
    if (isEmpty()) {
        return;
    }
    ListNode<T>* current = m_front;
    while (current != NULL && current->m_data != data) {
        current = current->m_next;
    }
    if (current == NULL) {
        return;
    }
    if (current == m_front) {
        m_front = current->m_next;
        if (m_front != NULL) {
            m_front->m_prev = NULL;
        } else {
            m_back = NULL;
        }
    } else if (current == m_back) {
        m_back = current->m_prev;
        if (m_back != NULL) {
            m_back->m_next = NULL;
        } else {
            m_front = NULL;
        }
    } else {
        current->m_prev->m_next = current->m_next;
        current->m_next->m_prev = current->m_prev;
    }
    delete current;
    --m_size;
}

template<typename T>
int DblList<T>::getSize() { // constant - O(1)
    return m_size;
}

template<typename T>
bool DblList<T>::isEmpty() { // constant - O(1)
    return (m_size == 0);
}

template<typename T>
void DblList<T>::addFront(T data) {
    ListNode<T>* newNode = new ListNode<T>(data);
    if (!isEmpty()) {
        m_front->m_prev = newNode;
        newNode->m_next = m_front;
    } else { // the list is empty
        m_back = newNode;
    }
    m_front = newNode;
    ++m_size;
}

template<typename T>
void DblList<T>::addBack(T data) {
    ListNode<T>* newNode = new ListNode<T>(data);
    if (!isEmpty()) {
        m_back->m_next = newNode;
        newNode->m_prev = m_back;
    } else {
        m_front = newNode;
    }
    m_back = newNode;
    ++m_size;
}

template<typename T>
void DblList<T>::add(int pos, T data) { // linear O(N)
    if (isEmpty()) {
        addFront(data);
    } else if (pos == 0) {
        addFront(data);
    } else if (pos >= m_size) {
        addBack(data);
    } else {
        ListNode<T>* current = m_front;
        int cPos = 0;
        while (cPos != pos) {
            current = current->m_next;
            ++cPos;
        }
        ListNode<T>* newNode = new ListNode<T>(data);
        current->m_prev->m_next = newNode;
        newNode->m_prev = current->m_prev;
        current->m_prev = newNode;
        newNode->m_next = current;
        ++m_size;
    }
}

template<typename T>
T DblList<T>::removeFront() {
    T data;
    data = m_front->m_data;
    if (m_size == 1) {
        delete m_front;
        m_front = NULL;
        m_back = NULL;
    }
    else {
        ListNode<T>* currFront = m_front;
        m_front = m_front->m_next;
        m_front->m_prev = NULL;
        delete currFront;
    }
    --m_size;
    return data;
}

template<typename T>
T DblList<T>::get(int pos) {
    ListNode<T>* current = m_front;
    int cPos = 0;
    while (cPos != pos) { // O(n)
        current = current->m_next;
        cPos++;
    } 
    return current->m_data;
}

template<typename T>
T DblList<T>::removeBack(){ //constant
    T data;
    data = m_back->m_data;
    //make sure not empty
    if(m_size == 1){
        delete m_back; //could also use m_front, since m_back and m_front point to the same place
        m_front = NULL;
        m_back = NULL;
    }else{
        ListNode<T>* currBack = m_back;
        m_back = m_back->m_prev;
        m_back->m_next = NULL;
        delete currBack;
    }
    --m_size;
    return data;
}

template<typename T>
T DblList<T>::remove(int pos) {
    T data;
    ListNode<T>* current = m_front;
    int cPos = 0;
    while (cPos != pos) {
        current = current->m_next;
        cPos++;
    }
    data = current->m_data;
    current->m_next->m_prev = current->m_prev;
    current->m_prev->m_next = current->m_next;
    delete current;
    return data;
}

#endif