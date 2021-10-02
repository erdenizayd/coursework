#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const T arr[], int arrSize);
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;

    int getNumberOfNodes() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    void insertAtTheHead(const T &data);
    void insertAtTheTail(const T &data);
    void insertSorted(const T &data);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();

    void print() const;

    T *toArray() const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    
private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const T arr[], int arrSize) {
    head = new Node<T>(arr[0],nullptr,nullptr);
    tail = head;
    for(int i = 1; i < arrSize; i++){
        Node<T> *newnode = new Node<T>(arr[i],tail,nullptr);
        tail->next = newnode;
        tail = newnode;
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    head = nullptr;
    tail = nullptr;
    if(!obj.isEmpty()){
        Node<T> *curr = obj.getFirstNode();
        while(curr){
            insertAtTheTail(curr->data);
            curr = curr->next;
        }
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node<T> *current = head;
    Node<T> *nextnode;
    while(current != nullptr){
        nextnode = current->next;
        delete current;
        current = nextnode;
    }
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    if(isEmpty()) return nullptr;
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    if(isEmpty()) return nullptr;
    return tail;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    Node<T> *curr;
    curr = head;
    if(isEmpty()){
        return nullptr;
    }
    while((curr->next != nullptr) && (curr->data != data)){
        curr = curr->next;
    }
    if(curr->data == data) return curr;
    return nullptr;

}

template<class T>
int LinkedList<T>::getNumberOfNodes() const {
    if(isEmpty()) return 0;
    else{
        int size = 0;
        Node<T> *curr;
        curr = head;
        while(curr != tail){
            size++;
            curr = curr->next;
        }
        size++;
        return size;
    }
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    if((head == nullptr) && (tail == nullptr)) return true;
    return false;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    Node<T> *curr;
    curr = head;
    if(isEmpty()) return false;
    while(curr){
        if(curr == node) return true;
        curr = curr->next;
    }
    return false;
}

template<class T>
void LinkedList<T>::insertAtTheHead(const T &data) {
    if(!isEmpty()){
        Node<T> *current;
        current = new Node<T>(data,nullptr,head);
        head->prev = current;
        head = current;
    }
    else{
        head = new Node<T>(data,nullptr,nullptr);
        tail = head;
    }
}

template<class T>
void LinkedList<T>::insertAtTheTail(const T &data) {
    if(isEmpty()){
        head = new Node<T>(data,nullptr,nullptr);
        tail = head;
    }
    else{
        Node<T> *newnode;
        newnode = new Node<T>(data,tail,nullptr);
        tail->next = newnode;
        tail = newnode;
    }
}

template<class T>
void LinkedList<T>::insertSorted(const T &data) {
    Node<T> *newnode;
    if(isEmpty()){
        newnode = new Node<T>(data,nullptr,nullptr);
        head = newnode;
        tail = newnode;
    }
    else if(data < head->data){
        newnode = new Node<T>(data,nullptr,head);
        head->prev = newnode;
        head = newnode;
    }
    else if(data > tail->data){
        newnode = new Node<T>(data,tail,nullptr);
        tail->next = newnode;
        tail = newnode;
    }
    else{
        Node<T> *curr = head;
        while(data > curr->data){
            curr = curr->next;
        }
        newnode = new Node<T>(data,nullptr,nullptr);
        newnode->next = curr;
        newnode->prev = curr->prev;
        curr->prev->next = newnode;
        curr->prev = newnode;
    }
    
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    if(contains(node)){
        if(head == tail){
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else if(head == node){
            Node<T> *curr;
            curr = head->next;
            delete head;
            head = curr;
            head->prev = nullptr;
        }
        else if(tail == node){
            Node<T> *curr;
            curr = tail->prev;
            delete tail;
            tail = curr;
            tail->next = nullptr;
        }
        else{
            Node<T> *curr = head;
            while(curr != node){
                curr = curr->next;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    if(!isEmpty()){
        if(head == tail){
            if(head->data == data){
                delete head;
                head = nullptr;
                tail = nullptr;
            }
        }
        else if(head->data == data){
            Node<T> *current;
            current = head->next;
            delete head;
            head = current;
            head->prev = nullptr;
        }
        else if(tail->data == data){
            Node<T> *current;
            current = tail->prev;
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        else{
            Node<T> *current = head;
            while(current && (current->data != data)){
                current = current->next;
            }
            if(current){
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    if(!isEmpty()){
        Node<T> *current = head;
        while(current != nullptr){
            current = current->next;
            delete head;
            head = current;
        }
        head = nullptr;
        tail = nullptr;
    }
}

template<class T>
void LinkedList<T>::print() const {
    std::cout << "Printing the linked list ..." << std::endl;

    if (this->isEmpty()) {
        std::cout << "empty" << std::endl;
        return;
    }

    Node<T> *node = this->head;

    while (node) {
        std::cout << *node << std::endl;
        node = node->next;
    }
}

template<class T>
T *LinkedList<T>::toArray() const {
    int length = getNumberOfNodes();
    T *array = new T[length];
    Node<T> *current;
    current = head;
    for(int i = 0; i < length ; i++){
        array[i] = current->data;
        current = current->next;
    }
    return array;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    if(rhs.isEmpty()){
        removeAllNodes();
    }
    else if((this != &rhs) && !rhs.isEmpty()){
        removeAllNodes();
        Node<T> *curr = rhs.head;
        while(curr){
            insertAtTheTail(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}


#endif //LINKEDLIST_H

