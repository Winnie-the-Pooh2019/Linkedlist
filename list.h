#pragma once

template<typename T>
struct SSListNode {
    T data;
    SSListNode* next;
    
    SSListNode() {
        next = nullptr;
    }
};

template<typename T>
struct SSList {
protected:
    SSListNode<T>* head;
    SSListNode<T>* tail;
    
    uint llength;
    
public:
    SSList() {
        head = nullptr;
        tail = nullptr;
        
        llength = 0;
    }
    
    ~SSList() {
        while ( llength != 0 ) {
            removeBack();
        }
    }

    void appendBack( T data ) {
        SSListNode<T>* node = new SSListNode<T>();
        node->data = data;
        
        llength++;
        
        if ( tail == nullptr ) {
            head = node;
            tail = head;
            return;
        }
        
        tail->next = node;
        tail = node;
    }
    
    void appendFront( T data ) {
        SSListNode<T>* node = new SSListNode<T>();
        node.data = data;
        
        llength++;
        
        if ( head == nullptr ) {
            head = node;
            tail = head;
            return;
        }
        
        node.next = head;
        head = node;
    }
    
    T removeBack() {
        if ( head == nullptr ) return T{};
        
        T data = tail->data;
        llength--;
        
        if ( head == tail ) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return data;
        }
        
        SSListNode<T>* node = head;
        
        while ( node->next != tail ) {
            node = node->next;
        }
        
        node->next = nullptr;
        delete tail;
        tail = node;
        
        return data;
    }
    
    T removeFront() {
        if ( head == nullptr ) return {};
        
        T data = head->data;
        llength--;
        
        if ( head == tail ) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return data;
        }
        
        SSListNode<T>* node = head->next;
        delete head;
        head = node;
        
        return data;
    }
    
    uint length() { return llength; }
};
