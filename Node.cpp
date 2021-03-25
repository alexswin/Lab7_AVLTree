#ifndef NODE_CPP
#define NODE_CPP

#include "Node.h"

Node::Node(int newData, Node* newLeft, Node* newRight) 
	: data(newData), left(newLeft), right(newRight) {
		int l_child_height;
		int r_child_height;

		if (newLeft == NULL) {
			l_child_height = 0;
		}
		else {
			l_child_height = newLeft->height;
		}
		
		if (newRight == NULL) {
			r_child_height = 0;
		}
		else {
			r_child_height = newRight->height;
		}

		if (l_child_height > r_child_height) {
			height = (1 + l_child_height);
		}
		else {
			height = (1 + r_child_height);
		}
	};

int Node::getData() const {
	return data;
}

Node* Node::getLeftChild() const {
	return left;
}

Node* Node::getRightChild() const {
	return right;
}

int Node::getHeight() {
	return height;
}

#endif