#pragma once
#include "list.h"

template<typename T>
struct SQueue {
private:
    SSList<T>* slist;
    
public:
    SQueue() {
        slist = new SSList<T>();
    }

    ~SQueue() {
        delete slist;
    }

    void push( T value ) {
        slist->appendBack( value );
    }
    
    T pop() {
        if ( slist->length() != 0 ) {
            return slist->removeFront();
        }
        
        return T{};
    }
    
    uint length() { return slist->length(); }
};
