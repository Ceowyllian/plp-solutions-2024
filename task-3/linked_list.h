#pragma once
#include <iterator>


class LinkedList {
protected:

	using value_type = int;
	using size_type = unsigned long long;

	struct Node {
		value_type value;
		Node* prev;
		Node* next;

		Node(value_type);

		void append(Node*);

		void prepend(Node*);
	};

	size_type length;
	Node* head;
	Node* tail;

	static void step_forward(Node*&);
	
	static void step_back(Node*&);
	
	Node* get_node_at(size_type) const;

	static void build_chain(const LinkedList&, Node*&, Node*&);

public:

	struct Iterator {
	public:
		friend class LinkedList;

		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = value_type;
		using pointer = value_type*;
		using reference = value_type&;

		Iterator(Node*);

		bool has_next() const;

		bool has_prev() const;

		reference operator*() const;

		pointer operator->() const;

		Iterator& operator++();

		Iterator operator++(int);

		Iterator& operator--();

		Iterator operator--(int);

		friend bool operator==(const Iterator&, const Iterator&);

		friend bool operator!=(const Iterator&, const Iterator&);

	private:

		Node* cursor;

		Node* node() const;
	};

	LinkedList();

	LinkedList(const LinkedList&);

	LinkedList(LinkedList&&);

	~LinkedList();

	virtual Iterator begin() const;

	virtual Iterator end() const;
	
	Iterator rbegin() const;

	Iterator rend() const;
	
	void print() const;

	void print_reverse() const;

	void push(value_type);

	value_type pop();

	void shift(value_type);

	value_type unshift();

	void clear();

	void extend(const LinkedList&);

	void extend(size_type, const LinkedList&);

	void insert_at(size_type, value_type);

	value_type remove_at(size_type);

	value_type first() const;

	value_type last() const;

	value_type get(size_type) const;

	size_type find_first(value_type) const;

	size_type find_last(value_type) const;

	void remove_first(value_type);

	void remove_last(value_type);

	size_type replace_all(value_type, value_type);

	size_type size() const;

	bool empty() const;

	value_type operator[](size_type) const;

	LinkedList* operator+(const LinkedList&);

	friend Node* Iterator::node() const;
};
