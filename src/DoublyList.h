template<typename T>
struct Node {
    T value;
    Node* next;
    Node* prev;

    Node(T data) : value(data), next(nullptr), prev(nullptr) {}

    ~Node() {
        next = prev = nullptr;
    }

};

template<typename T>
class DoublyList {
private:
    Node<T>* m_head = nullptr;
    Node<T>* m_tail = nullptr;

public:
    typedef Node<T>* Iterator;
    Iterator getHead() const {
        return m_head;
    }
    Iterator getTail() const {
        return m_tail;
    }
    T getValue(const Iterator& it) const {
        return it->value;
    }
    Iterator getNext(const Iterator& it) const {
        return it->next;
    }
    Iterator getPrev(const Iterator& it) const {
        return it->prev;
    }

    bool isEmpty() const {
        return !m_head || !m_tail;
    }

    void pushToHead(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (isEmpty()) {
            m_head = m_tail = newNode;
        } else {
            m_head->next = newNode;
            newNode->prev = m_head;
            m_head = newNode;
        }
    }

    void pushToTail(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (isEmpty()) {
            m_head = m_tail = newNode;
        } else {
            m_tail->prev = newNode;
            newNode->next = m_tail;
            m_tail = newNode;
        }
    }

    void pushAfter(const T& data, Iterator& it) {
        if (it == m_head)
            pushToHead(data);
        else {
            Node<T>* newNode = new Node<T>(data);
            newNode->next = it->next;
            newNode->prev = it;
            it->next->prev = newNode;
            it->next = newNode;
        }
    }

    void pushBefore(const T& data, Iterator& it) {
        if (it == m_tail)
            pushToTail(data);
        else {
            Node<T>* newNode = new Node<T>(data);
            newNode->next = it;
            newNode->prev = it->prev;
            it->prev->next = newNode;
            it->prev = newNode;
        }
    }

    T pop(Iterator& it) {
        if (isEmpty())
            return INT_MIN;

        T output = it->value;

        if (it == m_head == m_tail) {
            delete it;
            return output;
        }

        if (it == m_head) {
            m_head = it->prev;
            m_head->next = nullptr;
        }
        else if (it == m_tail) {
            m_tail = it->next;
            m_tail->prev = nullptr;
        }
        else {
            it->prev->next = it->next;
            it->next->prev = it->prev;
        }
        delete it;
        return output;
    }
};
