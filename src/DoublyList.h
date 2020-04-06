#pragma once
#include <limits>

template<typename T>
struct Node {
    T value;
    Node *next;
    Node *prev;

    Node(T data) : value(data), next(nullptr), prev(nullptr) {}

    ~Node() {
        next = prev = nullptr;
    }
};

template<typename T>
class DoublyList {
private:
    Node<T> *m_head = nullptr;
    Node<T> *m_tail = nullptr;

public:
    typedef Node<T> *Iterator;
    Iterator getHead() const {
        return m_head;
    }
    Iterator getTail() const {
        return m_tail;
    }
    T getValue(const Iterator &it) const {
        return it->value;
    }
    Iterator getNext(const Iterator &it) const {
        return it->next;
    }
    Iterator getPrev(const Iterator &it) const {
        return it->prev;
    }

    bool isEmpty() const {
        return !m_head || !m_tail;
    }

    void pushToTail(const T &data) {
        Node<T> *newNode = new Node<T>(data);
        if (isEmpty()) {
            m_head = m_tail = newNode;
        }
        else {
            m_tail->next = newNode;
            newNode->prev = m_tail;
            m_tail = newNode;
        }
    }

    void pushToHead(const T &data) {
        Node<T> *newNode = new Node<T>(data);
        if (isEmpty()) {
            m_head = m_tail = newNode;
        }
        else {
            m_head->prev = newNode;
            newNode->next = m_head;
            m_head = newNode;
        }
    }

    void pushAfter(const T &data, const int &pos) {
        Node<T> *newNode = new Node<T>(data);

        if (isEmpty())
            m_head = m_tail = newNode;
        else {
            Iterator it = getHead();
            for (int i = 0; i < pos - 1 && it->next; ++i)
                it = it->next;

            if (!it) return;

            newNode->next = it->next;
            newNode->prev = it;
            if (it != m_tail)
                it->next->prev = newNode;
            it->next = newNode;
        }
    }

    void pushAfter(const T &data, const Iterator &pos) {
        if (!pos) return;

        if (pos == m_tail)
            pushToTail(data);
        else if (pos == m_head)
            pushAfter(data, 1);   // first node - head
        else {
            Node<T> *newNode = new Node<T>(data);
            newNode->next = pos->next;
            newNode->prev = pos;
            pos->next->prev = newNode;
            pos->next = newNode;
        }
    }

    T pop(const int &pos) {
        if (isEmpty()) return std::numeric_limits<int>::min();

        Iterator iter = getHead();
        for (int i = 0; i < pos && iter; ++i)
            iter = getNext(iter);

        if (!iter) return std::numeric_limits<int>::min();

        T output = iter->value;

        if (iter == m_head && iter == m_tail) {
            delete iter;
            m_head = m_tail = nullptr;
            return output;
        }

        if (iter == m_tail) {
            m_tail = iter->prev;
            m_tail->next = nullptr;
        }
        else if (iter == m_head) {
            m_head = iter->next;
            m_head->prev = nullptr;
        }
        else {
            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;
        }

        delete iter;
        return output;
    }

    T pop(Iterator &iter) {
        if (isEmpty()) return std::numeric_limits<int>::min();

        Iterator oldIter(iter);

        T output = oldIter->value;

        if (oldIter == m_head && oldIter == m_tail) {
            delete oldIter;
            m_head = m_tail = nullptr;
            return output;
        }

        if (oldIter == m_tail) {
            m_tail = oldIter->prev;
            m_tail->next = nullptr;
        }
        else if (oldIter == m_head) {
            m_head = oldIter->next;
            m_head->prev = nullptr;
        }
        else {
            oldIter->prev->next = oldIter->next;
            oldIter->next->prev = oldIter->prev;
        }

        delete oldIter;
        return output;
    }

    void clear() {
        while (!isEmpty()) {
            pop(m_head);
        }
    }

    void sort() {                        // assume list isn't empty
        if (m_head != m_tail) {          // one node = nothing to sort
            Iterator node = m_head;
            while (node->next) {
                Iterator current = node;
                if (current->next->value < current->value) {
                    T valueToPush = pop(current->next);
                    while (current->prev && valueToPush < current->value)
                        current = current->prev;
                    if (current == m_head)
                        pushToHead(valueToPush);
                    else
                        pushAfter(valueToPush, current);
                }
                else
                    node = node->next;
            }
        }
    }
};
