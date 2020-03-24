#pragma once
#include <limits>

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

	void pushAfter(const T& data, const int& pos) {
		Node<T>* newNode = new Node<T>(data);

		if (isEmpty())
			m_head = m_tail = newNode;
		else {
			DoublyList<T>::Iterator it = getTail();
			for (int i = 0; i < pos - 1 && it->next; ++i)
				it = it->next;

			if (!it) return;

			if (it == m_head)
				pushToHead(data);
			else {
				newNode->next = it->next;
				newNode->prev = it;
				it->next->prev = newNode;
				it->next = newNode;
			}
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

	T pop(const int& pos) {
		if (isEmpty()) return std::numeric_limits<int>::min();

		DoublyList<T>::Iterator iter = getTail();
		for (int i = 0; i < pos; ++i)
			iter = getNext(iter);

		if (!iter) return std::numeric_limits<int>::min();

		T output = iter->value;

		if (iter == m_head && iter == m_tail) {
			delete iter;
			m_head = m_tail = nullptr;
			return output;
		}

		if (iter == m_head) {
			m_head = iter->prev;
			m_head->next = nullptr;
		} else if (iter == m_tail) {
			m_tail = iter->next;
			m_tail->prev = nullptr;
		} else {
			iter->prev->next = iter->next;
			iter->next->prev = iter->prev;
		}

		delete iter;
		iter = nullptr;
		return output;
	}

	T pop(Iterator& iter) {
		if (isEmpty()) return std::numeric_limits<int>::min();

		T output = iter->value;

		if (iter == m_head && iter == m_tail) {
			delete iter;
			m_head = m_tail = nullptr;
			return output;
		}

		if (iter == m_head) {
			m_head = iter->prev;
			m_head->next = nullptr;
		} else if (iter == m_tail) {
			m_tail = iter->next;
			m_tail->prev = nullptr;
		} else {
			iter->prev->next = iter->next;
			iter->next->prev = iter->prev;
		}

		delete iter;
		iter = nullptr;
		return output;
	}

	void clear() {
		while (!isEmpty()) {
			pop(m_head);
		}
	}
};
