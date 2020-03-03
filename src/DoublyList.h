template<typename T>
struct Node {
	T value;
	Node* next;
	Node* prev;

	Node(T data) : value(data), next(nullptr), prev(nullptr) {
	}

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
	Iterator head() {
		return m_head;
	}
	Iterator tail() {
		return m_tail;
	}


};
