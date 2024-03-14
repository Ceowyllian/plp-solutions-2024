#pragma once
#include "stdexcept"
#include "iostream"
#include "iterator"
#include "linked_list.h"


LinkedList::Node::Node(value_type value) {
	this->value = value;
	this->prev = nullptr;
	this->next = nullptr;
}


void LinkedList::Node::append(Node* node) {
	next = node;
	node->prev = this;
}


void LinkedList::Node::prepend(Node* node) {
	prev = node;
	node->next = this;
}


void LinkedList::step_forward(Node*& node) {
	node = node->next;
}


void LinkedList::step_back(Node*& node) {
	node = node->prev;
}


LinkedList::Node* LinkedList::get_node_at(size_type index) const {
	if (index > length)
		throw std::out_of_range("The index is out of range.");
	
	if (empty())
		throw std::length_error("The list is empty.");

	bool closer_to_head = index <= (length >> 1);
	Iterator cursor = closer_to_head ? this->begin() : this->end();

	if (closer_to_head)
		for (size_type i = 0; i < index; i++, cursor++);
	else
		for (size_type i = length; i > index; i--, cursor--);

	return cursor.node();
}


void LinkedList::build_chain(
	const LinkedList& list, Node*& chain_head, Node*& chain_tail
) {
	if (list.empty())
		throw new std::length_error("Source list is empty.");

	Iterator cursor = list.begin();
	chain_tail = new Node(*cursor);
	chain_head = chain_tail;
	
	while (cursor.has_next()) {
		cursor++;
		chain_tail->append(new Node(*cursor));
		step_forward(chain_tail);
	}

	chain_tail = cursor.node();
}


LinkedList::LinkedList() {
	length = 0;
	head = tail = nullptr;
}


LinkedList::LinkedList(const LinkedList& other) {
	build_chain(other, head, tail);
	length = other.size();
}


LinkedList::LinkedList(LinkedList&& other) {
	head = other.head;
	tail = other.tail;
	length = other.length;
	other.head = nullptr;
	other.tail = nullptr;
	other.length = 0;
}


LinkedList::~LinkedList() { clear(); }


LinkedList::Iterator LinkedList::begin() const {
	return Iterator(this->head);
}


LinkedList::Iterator LinkedList::end() const {
	return Iterator(nullptr);
}


LinkedList::Iterator LinkedList::rbegin() const {
	return Iterator(this->tail);
}


LinkedList::Iterator LinkedList::rend() const {
	return Iterator(nullptr);
}


void LinkedList::print() const {
	std::cout << '[';
	for (value_type e: *this)
		std::cout << e << ", ";
	std::cout << "]\n";
}


void LinkedList::print_reverse() const {
	std::cout << '[';
	for (auto i = rbegin(); i != rend(); i--)
		std::cout << *i << ", ";
	std::cout << "]\n";
}


void LinkedList::push(value_type value) {
	Node* node = new Node(value);

	if (empty()) 
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->append(node);
		step_forward(tail);
	}

	length++;
}


LinkedList::value_type LinkedList::pop() {
	if (empty()) 
		throw std::length_error("The list is empty.");

	value_type value = tail->value;
	Node* prev = tail->prev;
	delete tail;

	if (length == 1) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		prev->next = nullptr;
		tail = prev;
	}

	length--;
	return value;
}


void LinkedList::shift(value_type value) {
	Node* node = new Node(value);
	node->value = value;

	if (empty()) {
		head = node;
		tail = node;
	}
	else {
		head->prepend(node);
		step_back(head);
	}
	length++;
}


LinkedList::value_type LinkedList::unshift() {
	if (empty())
		throw std::length_error("The list is empty.");

	value_type value = head->value;
	Node* next = head->next;
	delete head;

	if (length == 1) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		next->prev = nullptr;
		head = next;
	}

	length--;
	return value;
}


void LinkedList::clear() {
	while (!empty())
		pop();
}


void LinkedList::extend(const LinkedList& other) {
	for (value_type value : other)
		push(value);
}


void LinkedList::extend(size_type index, const LinkedList& other) {

	if (other.empty()) return;

	Node* chain_head;
	Node* chain_tail;
	build_chain(other, chain_head, chain_tail);

	if (empty()) {
		head = chain_head;
		tail = chain_tail;
	}
	else if (index == 0) {
		chain_tail->append(head);
		head = chain_head;
	}
	else if (index == length) {
		chain_head->prepend(tail);
		tail = chain_tail;
	}
	else {
		Node* right = get_node_at(index);
		Node* left = right->prev;
		chain_tail->append(right);
		if (left)
			chain_head->prepend(left);
	}

	length += other.size();
}


void LinkedList::insert_at(size_type index, value_type value) {
	if (index == 0) 
		shift(value);

	if (index == length)
		push(value);

	Node* right = get_node_at(index);
	Node* left = right->prev;
	Node* new_node = new Node(value);

	right->append(new_node);
	left->prepend(new_node);

	length++;
}


LinkedList::value_type LinkedList::remove_at(size_type index) {
	Node* node = get_node_at(index);
	value_type value = node->value;

	Node* left = node->prev;
	Node* right = node->next;

	if (length == 1)
		head = tail = nullptr;

	if (left != nullptr)
		left->append(right);

	if (right != nullptr)
		right->prepend(left);

	length--;

	return value;
}


LinkedList::value_type LinkedList::first() const {
	return get(0);
}


LinkedList::value_type LinkedList::last() const {
	return get(length - 1);
}


LinkedList::value_type LinkedList::get(size_type index) const {
	return get_node_at(index)->value;
}


LinkedList::size_type LinkedList::find_first(value_type value) const {
	size_type i = 0;
	for (Iterator cursor = begin(); cursor != end(); cursor++, i++)
		if (value = *cursor)
			return i;
	return -1;
}


LinkedList::size_type LinkedList::find_last(value_type value) const {
	size_type i = 0;
	for (Iterator cursor = rbegin(); cursor != rend(); cursor++, i++)
		if (value = *cursor)
			return i;
	return -1;
}


void LinkedList::remove_first(value_type value) {
	size_type index = find_first(value);
	if (index != -1) remove_at(index);
}


void LinkedList::remove_last(value_type value) {
	size_type index = find_last(value);
	if (index != -1) remove_at(index);
}


LinkedList::size_type LinkedList::replace_all(
	value_type old_value, value_type new_value
) {
	size_type count = 0;

	for (Iterator cursor = begin(); cursor != end(); cursor++)
		if (*cursor == old_value) {
			cursor.node()->value = new_value;
			count++;
		}

	return count;
}


LinkedList::size_type LinkedList::size() const {
	return length;
}


bool LinkedList::empty() const {
	return length == 0;
}


LinkedList::value_type LinkedList::operator[](size_type index) const {
	return get(index);
}


LinkedList* LinkedList::operator+(const LinkedList& other) {
	this->extend(other);
	return this;
}
