#pragma once
#include "list.h"

template<typename T>
struct SStack {
private:
    SSList<T>* slist;
    
public:
    SStack() {
        slist = new SSList<T>();
    }

    ~SStack() {
        delete slist;
    }

    void push( T value ) {
        slist->appendBack( value );
    }
    
    T pop() {
        if ( slist->length() != 0 ) {
            return slist->removeBack();
        }
        
        return T{};
    }
    
    uint length() { return slist->length(); }
};
