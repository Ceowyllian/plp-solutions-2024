#pragma once
#include "linked_list.h"


using Iterator = LinkedList::Iterator;
using value_type = Iterator::value_type;
using pointer = Iterator::pointer;
using reference = Iterator::reference;


Iterator::Iterator(Node* ptr) {
	cursor = ptr;
}


bool Iterator::has_next() const {
	return (this->cursor != nullptr) && (this->cursor->next != nullptr);
}


bool Iterator::has_prev() const {
	return (this->cursor != nullptr) && (this->cursor->prev != nullptr);
}


LinkedList::Node* Iterator::node() const{
	return cursor;
}


reference Iterator::operator*() const {
	return cursor->value;
}


pointer Iterator::operator->() const {
	return &(cursor->value);
}


Iterator& Iterator::operator++() {
	this->cursor = this->cursor->next;
	return *this;
}


Iterator Iterator::operator++(int) {
	Iterator tmp = *this;
	++(*this);
	return tmp;
}


Iterator& Iterator::operator--() {
	cursor = cursor->prev;
	return *this;
}

Iterator Iterator::operator--(int) {
	Iterator tmp = *this;
	--(*this);
	return tmp;
}


bool operator==(const Iterator& a, const Iterator& b) {
	return a.cursor == b.cursor;
}


bool operator!=(const Iterator& a, const Iterator& b) {
	return a.cursor != b.cursor;
}
