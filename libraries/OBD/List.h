#ifndef __LIST_H
#define __LIST_H

#include <Arduino.h>
#include <stddef.h>

template<class T>
struct ListItem
{
    T data;
    ListItem<T> *next;
};

template<typename T>
class List
{
    public:
        List();
        ~List();
        virtual ListItem<T>* getNode(uint16_t index);
        virtual T next();
        virtual void rewind();
        virtual bool add(T);
        virtual uint16_t size();
    private:
        ListItem<T> *top;
        ListItem<T> *bottom;
        ListItem<T> *current;
        uint16_t _size;
};

// ctor
template<typename T>
List<T>::List()
{
    top = NULL;
    bottom = NULL;
    current = NULL;
    _size = 0;
}

// dtor
template<typename T>
List<T>::~List()
{
    ListItem<T> *cur;
    while (top != NULL) {
        cur = top;
        top = top->next;
        delete cur;
    }
    bottom = NULL;
    _size = 0;
}

template<typename T>
ListItem<T>* List<T>::getNode(uint16_t index)
{
    uint16_t idx = 0;

    ListItem<T> *cur = top;

    while (idx < index && cur) {
        cur = cur->next;
        idx++;
    }

    if (idx == index) {
        return cur;
    }

    return false;
}

template<typename T>
bool List<T>::add(T t)
{
    ListItem<T> *tmp = new ListItem<T>();
    tmp->data = t;
    tmp->next = NULL;

    if (top) {
        bottom->next = tmp;
    } else {
        top = tmp;
    }

    _size++;

    return true;
}

template<typename T>
T List<T>::next()
{
    if (_size == 0){
        return T();
    }

    if (current == NULL) {
        current = top;
        return current->data;
    }

    if (current == bottom) {
        return T();
    }

    current = current->next;

    return current->data;
}

template<typename T>
void List<T>::rewind()
{
    current = NULL;
}

template<typename T>
uint16_t List<T>::size()
{
    return _size;
}

#endif