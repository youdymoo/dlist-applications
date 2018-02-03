#include <cstdlib>
#include "dlist.h"

using namespace std;

template<class T>
bool Dlist<T> :: isEmpty() const {
    return (first == NULL) && (last == NULL);
}

template<class T>
void Dlist<T> :: insertFront(T *op) {
    node *np = new node;
    np->op = op;
    np->next = first;
    np->prev = NULL;

    if (!isEmpty()) {
        first->prev = np;
    } else {
        last = np;
    }

    first = np;
    return;
}

template<class T>
void Dlist<T> :: insertBack(T *op) {
    node *np = new node;
    np->op = op;
    np->prev = last;
    np->next = NULL;

    if (!isEmpty()) {
        last->next = np;
    } else {
        first = np;
    }

    last = np;
    return;
}

template<class T>
T *Dlist<T> :: removeFront() {
    if (isEmpty()) {
        emptyList e;
        throw e;
    }

    node *victim = first;
    first = victim->next;

    if (first == NULL) {
        last = NULL;
    } else {
        first->prev = NULL;
    }

    T *op = victim->op;
    delete victim;
    return op;
}

template<class T>
T *Dlist<T> :: removeBack() {
    if (isEmpty()) {
        emptyList e;
        throw e;
    }

    node *victim = last;
    last = victim->prev;
    if (last == NULL) {
        first = NULL;
    } else {
        last->next = NULL;
    }

    T *op = victim->op;
    delete victim;
    return op;
}

template<class T>
Dlist<T> :: Dlist() {
    first = NULL;
    last = NULL;
}

template<class T>
Dlist<T> :: Dlist(const Dlist &l) {
    first = NULL;
    last = NULL;
    copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T> :: operator=(const Dlist &l) {
    copyAll(l);
    return *this;
}

template<class T>
Dlist<T> :: ~Dlist() {
    removeAll();
}

template<class T>
void Dlist<T> :: removeAll() {
    while (!isEmpty()) {
        T *op = removeFront();
        delete op;
    }
    return;
}

template<class T>
void Dlist<T> :: copyAll(const Dlist &l) {
    removeAll();
    node *np = l.first;

    while (np != NULL) {
        T *op = new T(*np->op);
        insertBack(op);
        np = np->next;
    }
    
    return;
}