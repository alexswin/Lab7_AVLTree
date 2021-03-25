#ifndef AVL_CPP
#define AVL_CPP

#include "AVL.h"

AVL::AVL();

AVL::~AVL();

Node* AVL::getRootNode() const;

bool AVL::add(int data);

bool AVL::remove(int data);

void AVL::clear();

void AVL::clear(Node* &subRoot);

bool AVL::add(int data, Node* &subRoot);

bool AVL::remove(int data, Node* &subRoot);

int AVL::updateHeight(Node* n) {
	if (n == NULL) {
		return 0;
	}
	int l_child_height = updateHeight(n->left);
	int r_child_height = updateHeight(n->right);
	if (l_child_height > r_child_height) {
		n->height = (1 + l_child_height);
	}
	else {
		n->height = (1 + r_child_height);
	}
	return n->height;
}

#endif