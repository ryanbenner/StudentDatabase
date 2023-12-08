

#ifndef LAZYBST_H
#define LAZYBST_H

#include "TreeNode.h"
#include "FileProcessor.h"
#include "Database.h"
#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();
        int getSize();
        void insert(T data); // inserts a student
        void remove(T data);
        T find(T data); // finds a student based on ID
        void printTreeInOrder();
        void printTreeInOrderToFile(std::ostream& os) const; // prints to file
    
    private:
        TreeNode<T>* m_root;
        int m_size;
        void insertHelper(TreeNode<T>*& subTreeRoot, T& data); // helps insert stu/fac based on ID
        T findHelper(TreeNode<T>*& subTreeRoot, T data); // helps find a student/faculty based on ID
        void printTreeInOrderHelper(TreeNode<T>* subTreeRoot);
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        TreeNode<T>* getSuccessor(TreeNode<T>* rightChild);
        void rebuildTree(T* sortedData, int start, int end, TreeNode<T>*& subTreeRoot); // rebuilds tree
        void collectDataInOrder(TreeNode<T>* subTreeRoot, T* data, int& index); // collects node data in order, to rebuild
        int getNodeDepth(TreeNode<T>* node); // gets a nodes depth
        void printTreeInOrderToFileHelper(TreeNode<T>* subTreeRoot, std::ostream& os) const; // helps print to file
};

template <typename T>
LazyBST<T>::LazyBST(){
    m_root = NULL;
    m_size = 0;
}

template <typename T>
LazyBST<T>::~LazyBST(){
    //free memory
    if(m_root != NULL){
        delete m_root;
  }
}

template <typename T>
void LazyBST<T>::printTreeInOrderToFile(std::ostream& os) const {
    printTreeInOrderToFileHelper(m_root, os);
}

template <typename T>
void LazyBST<T>::printTreeInOrderToFileHelper(TreeNode<T>* subTreeRoot, std::ostream& os) const {
    if (subTreeRoot != nullptr) {
        printTreeInOrderToFileHelper(subTreeRoot->m_left, os);
        os << *(subTreeRoot->m_data) << "\n";
        printTreeInOrderToFileHelper(subTreeRoot->m_right, os);
    }
}

template <typename T>
int LazyBST<T>::getSize(){
    return m_size;
}

template <typename T>
void LazyBST<T>::insert(T data){
    insertHelper(m_root, data);
    ++m_size;

    if (getNodeDepth(m_root->m_right) != 0 && getNodeDepth(m_root->m_left) != 0) {
        if (m_root != nullptr && std::max(getNodeDepth(m_root->m_left)/getNodeDepth(m_root->m_right), getNodeDepth(m_root->m_right)/getNodeDepth(m_root->m_left)) > 1.5) {
            // Rebuild the tree
            int size = getSize();
            T* sortedData = new T[size];
            int index = 0;
            collectDataInOrder(m_root, sortedData, index);
            for (int i = 0; i < size; i++) {
                cout << sortedData[i] << " ";
            }
            cout << endl;
            rebuildTree(sortedData, 0, size - 1, m_root);
            delete[] sortedData;

        }
    }
}

template <typename T>
void LazyBST<T>::insertHelper(TreeNode<T>*& subTreeRoot, T& data){
    if(subTreeRoot == NULL){
        subTreeRoot = new TreeNode<T>(data); //pointer swap
    } 
    else if(*(data) < *(subTreeRoot->m_data)){
        insertHelper(subTreeRoot->m_left, data);
    } 
    else if(*(data) > *(subTreeRoot->m_data)){
        insertHelper(subTreeRoot->m_right, data);
    }
}

template <typename T>
T LazyBST<T>::find(T data){
    return findHelper(m_root, data);
}

template <typename T>
T LazyBST<T>::findHelper(TreeNode<T>*& subTreeRoot, T data){
    if(subTreeRoot == NULL){
        return subTreeRoot->m_data;
    }else if(*(data) == *(subTreeRoot->m_data)){
        return subTreeRoot->m_data;
    }else if(*(data) < *(subTreeRoot->m_data)){
        return findHelper(subTreeRoot->m_left, data);
    }else{
        return findHelper(subTreeRoot->m_right, data);
    }
}

template <typename T>
int LazyBST<T>::getNodeDepth(TreeNode<T>* node) {
    if (node == NULL) {
        return 0;
    }
    int lHeight = getNodeDepth(node->m_left);
    int rHeight = getNodeDepth(node->m_right);
    if (lHeight > rHeight) {
        return (lHeight + 1);
    } else {
        return (rHeight + 1);
    }
}

template <typename T>
void LazyBST<T>::collectDataInOrder(TreeNode<T>* subTreeRoot, T* data, int& index) {
    if (subTreeRoot != NULL) {
        collectDataInOrder(subTreeRoot->m_left, data, index);
        data[index++] = subTreeRoot->m_data;
        collectDataInOrder(subTreeRoot->m_right, data, index);
    }
}

template <typename T>
void LazyBST<T>::rebuildTree(T* sortedData, int start, int end, TreeNode<T>*& subTreeRoot) {
    if (start <= end) {
        int mid = std::ceil(start + (end - start) / 2);
        // cout << "INSERTING: " << sortedData[mid] << endl;
        subTreeRoot = new TreeNode<T>(sortedData[mid]);
        rebuildTree(sortedData, start, mid - 1, subTreeRoot->m_left);
        rebuildTree(sortedData, mid + 1, end, subTreeRoot->m_right);
    }
}

template <typename T>
void LazyBST<T>::printTreeInOrder(){
    printTreeInOrderHelper(m_root);
}

template <typename T>
void LazyBST<T>::printTreeInOrderHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot != NULL){
        printTreeInOrderHelper(subTreeRoot -> m_left);
        cout << *(subTreeRoot->m_data) << endl;
        printTreeInOrderHelper(subTreeRoot -> m_right);
    }
}

template <typename T>
void LazyBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
    while(target != NULL && target->m_data != key){
        parent = target;
        if(key < target->m_data){
            target = target->m_left;
        }else{
            target = target->m_right;
        }
    }
}

template <typename T>
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T>* rightChild){
    while(rightChild->m_left != NULL){
        rightChild = rightChild->m_left;
    }
    return rightChild;
}

template <typename T>
void LazyBST<T>::remove(T d){
    //TODO - check if empty 
    TreeNode<T>* target = NULL;
    TreeNode<T>* parent = NULL;
    target = m_root;
    findTarget(d,target, parent);
    if(target == NULL){ //not in the tree, nothing to do
        return;
    }
    if(target->m_left == NULL && target->m_right == NULL){ //no children, it's a leaf
        if(target == m_root){
            m_root = NULL;
        }else{ //it's not the root
            if(target == parent->m_left){
                parent->m_left = NULL;
            }else{
                parent->m_right = NULL;
            }
        }
    }else if(target->m_left != NULL && target->m_right !=NULL){ // 2 child case
        TreeNode<T>* suc = getSuccessor(target->m_right);
        T value = suc->m_data;
        remove(value);
        target->m_data = value;
    }else{ // 1 child case
        TreeNode<T>* child;
        if(target->m_left != NULL){
            child = target->m_left;
        }else{
            child = target->m_right;
        }
        if(target == m_root){
            m_root = child;
        }else{
            if(target == parent->m_left){
                parent->m_left = child;
            }else{
                parent->m_right = child;
            }
        }

    }
    --m_size;
}

#endif