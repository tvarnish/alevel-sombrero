#include <iostream>
#include "linkedlist.h"

using namespace std;

Node::Node() {
	next = NULL;
}

List::List() {
	head = NULL;
	length = 0;
}

void List::Append(Node * node) {
	Node * pointer = head;

	if (head == NULL) {
		head = node;
	}
	else {
		while (pointer->next != NULL) {
			pointer = pointer->next;
		}

		pointer->next = node;
	}
}

void List::Display() {
	Node * pointer = head;

	while (pointer != NULL) {
		cout << pointer->data << ", ";
		pointer = pointer->next;
	}

	cout << endl;
}
