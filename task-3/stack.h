#pragma once
#include "linked_list.h"


class Stack : private LinkedList {
public:
	using LinkedList::push;
	using LinkedList::pop;
	using LinkedList::clear;
	using LinkedList::size;
	using LinkedList::empty;
	using LinkedList::Iterator;

	value_type top() {
		return tail->value;
	}
	
	Iterator begin() const override {
		return rbegin();
	}

	Iterator end() const override {
		return rend();
	}

};
