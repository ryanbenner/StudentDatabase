

#ifndef P_QUEUE_H
#define P_QUEUE_H
#include "DblList.h"

template <typename T>
class PQueue{
    public:
        PQueue(bool isMin); //min queue or not
        virtual ~PQueue();
        void add(T data);
        T remove();
        int size();
        bool isEmpty();
        T peek();
        T get(int pos);
        T removeAt(int pos);
        void removeData(T data);
    private:
        bool isMinQ;
        DblList<T>* m_list;
};

template <typename T>
PQueue<T>::PQueue(bool isMin){
    isMinQ = isMin;
    m_list = new DblList<T>();
}

template <typename T>
PQueue<T>::~PQueue(){
}

template <typename T>
bool PQueue<T>::isEmpty(){
    return m_list->isEmpty();
}

template <typename T>
int PQueue<T>::size(){
    return m_list->getSize();
}

template <typename T>
T PQueue<T>::remove(){
    if(isMinQ){
        return m_list->removeFront(); //smallest always at front
    } else {
        return m_list->removeBack(); //largest always at back
    }
}

template <typename T>
void PQueue<T>::add(T d){
    if(isEmpty()){ //well, that's easy. Just add.
        m_list->addFront(d);
    }
    else {
        ListNode<T>* newNode = new ListNode<T>(d);
        int currIdx = 0;
        ListNode<T>* currNode = m_list->m_front;
        while(currNode != NULL && currNode->m_data < d){ //from front, find the rightplace to add. The < operator better be defined on the class.
            ++currIdx;
            currNode = currNode->m_next;
        }
        m_list->add(currIdx,d); //this is a hack because it starts over looking from front. But doesn't change linear runtime. Just 2x as slow in practice.
    }
}

template <typename T>
T PQueue<T>::get(int pos) {
    return m_list->get(pos);
}

template <typename T>
T PQueue<T>::removeAt(int pos) {
    return m_list->remove(pos);
}

template <typename T>
void PQueue<T>::removeData(T data) {
    int currIdx = 0;
    ListNode<T>* currNode = m_list->m_front;
    while (currNode != NULL && currNode->m_data != data) {
        ++currIdx;
        currNode = currNode->m_next;
    }
    if (currNode->m_data == data) {
        m_list->remove(currIdx);
    }
}

#endif
