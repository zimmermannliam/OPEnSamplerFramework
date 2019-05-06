//
//  LinkedList.hpp
//  OPEnSamplerFramework
//
//  Created by Kawin on 2/10/19.
//  Copyright © 2019 Kawin. All rights reserved.
//

#pragma once

/*
    Implementation of doubly linkedlist
*/
template <typename T>
class LinkedList {
protected:
    struct Node {
    public:
        T data;
        Node * next = nullptr;
        Node * prev = nullptr;
        
    public:
        Node(T data) : data(data) {}
    };
    
    Node * head = nullptr;
    Node * tail = nullptr;
    
    friend class OPSystem;
/*
    Subclass Interfacing
 */
protected:
    void deInit() {
        auto current = head;
        while (current) {
            auto trash = current;
            current = current->next;
            delete trash;
        }

        size = 0;
        head = nullptr;
        tail = nullptr;
    }
    
    void append(Node * node) {
        if (head == nullptr) {
            head = node;
            tail = node;
        } else if (head == tail) {
            tail = node;
            head->next = tail;
            tail->prev = head;
        } else {
            auto last = tail;
            tail = node;
            tail->prev = last;
            last->next = tail;
        }

        size++;
    }

    Node * searchFromHead(int index) {
        if (invalidateIndex(index) == false) {
            return nullptr;
        }
        
        auto current = head;
        int i = 0;
        while(i != index) {
            current = current->next;
            i++;
        }
        
        return current;
    }
    
    Node * searchFromTail(int index) {
        if (invalidateIndex(index) == false) {
            return nullptr;
        }
        
        auto current = tail;
        int i = size - 1;
        while (i != index) {
            current = current->prev;
            i--;
        }
        
        return current;
    }

    Node * search(int index) {
        return index < size /2 ? searchFromHead(index) : searchFromTail(index);
    }
    
/*
    Public methods
 */
public:
    int size = 0;
    
    LinkedList<T>(){
        
    };
    
    // Copy-constructor override
    LinkedList<T>(const LinkedList<T> &obj) {
        auto source = obj.head;
        while (source) {
            auto node = new Node(*source);
            node->prev = nullptr;
            node->next = nullptr;
            append(node);
            source = source->next;
        }
    }
    
    // Copy-assignment operator override
    LinkedList<T> & operator =(LinkedList<T> const & rhs) {
        deInit();
        extend(rhs);
        return * this;
    }
    
    ~LinkedList<T>() {
        deInit();
    }

    bool isEmpty() {
        return size == 0;
    }
    
    void append(T data) {
        auto node = new Node(data);
        append(node);
    }
    
    void extend(LinkedList<T> const & other) {
        auto source = other.head;
        while (source) {
            auto node = new Node(*source);
            node->next = nullptr;
            node->prev = nullptr;
            append(node);
            source = source->next;
        }
    }

    bool invalidateIndex(int index) {
        if (index < 0 || index > size - 1) {
            Serial.print(F("Index out of range: "));
            Serial.println(index);
            return false;
        }
        
        return true;
    }
    
    /*
        Care must be taken when call this method. 
        If index is invalid then the program will crash because of nullptr returned from searching.
    */
    T & get(int index) {
        auto target = index < size /2 ? searchFromHead(index) : searchFromTail(index);
        if (target) {
            return (target->data);
        } else {
            Serial.println(F("Illegal access"));
            while(true);
        }
    }

    bool remove(int index) {
        if (invalidateIndex(index) == false) {
            return false;
        }
        
        /*
            Cut the searching time by 50% on average.
            (1) Only one element in the list. Target is automatically head for a valid index.
            (2) Special case where we are at head and only two nodes left.
            (3) At head
            (4) At body
            (5) At tail
        */
        auto target = index < size / 2 ? searchFromHead(index) : searchFromTail(index);
        if (head == tail) {                     // (1)
            head = nullptr;
            tail = nullptr;
        } else if (index == 0 && size == 2) {   // (2)
            head = tail;
            tail->prev = nullptr;
        } else if (index == 0) {                // (3)
            head = head->next;
        } else if (target->next) {              // (4)
            auto prev = target->prev;
            auto next = target->next;
            prev->next = next;
            next->prev = prev;
        } else {                                // (5)
            auto prev = target->prev;
            tail = prev;
            tail->next = nullptr;
        }

        size--;
        delete target;
        return true;
    }

    bool remove(Node * nodeptr) {
        if (nodeptr == nullptr) {
            return false;
        }

        int index = 0;
        auto current = head;
        while (current) {
            if (current == nodeptr) {
                break;
            }

            index++;
            current = current->next;
        }

        if (current) {
            remove(index);
            return true;
        } else {
            return false;
        }
    }
    
    void printNodes() {
        Serial.println(F("Node List: "));
        auto current = head;
        int i = 0;
        while (current) {
            Serial.print(F("["));
            Serial.print(i);
            Serial.print(F("] "));
            Serial.println((unsigned int) current, HEX);
            current = current->next;
            i++;
        }
    }
};
