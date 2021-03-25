#ifndef AVL_CPP
#define AVL_CPP

#include "AVL.h"

AVL::AVL() : root(NULL) {};

AVL::~AVL() {
	clear();
}

Node* AVL::getRootNode() const {
	return root;
}

bool AVL::add(int data) {
	return add(data, root);
}

bool AVL::remove(int data) {
	return remove(data, root);
}

void AVL::clear() {
	clear(root);
}

void AVL::clear(Node* &subRoot) {
	//cout << "In clear." << endl;
	if (subRoot == NULL) {
		//cout << "subRoot is NULL. Returning..." << endl;
		return;
	}
	//else {cout << "subRoot is " << subRoot->data << ". Clearing left and right children..." << endl;}
	clear(subRoot->left);
	clear(subRoot->right);
	//cout << "Deleting node " << subRoot->data << endl;
	delete subRoot;
	subRoot = NULL;
	//cout << "Returning..." << endl;
}

bool AVL::add(int data, Node* &subRoot) {
	//cout << "In add. Attempting to add " << data << endl;
	if (subRoot == NULL) {
		//cout << "Empty subtree. Adding " << data << "..." << endl;
		subRoot = new Node(data);
		//cout << "Added new node with " << subRoot->data << ". Returning..." << endl;
		return true;
	}
	else if (data < subRoot->data) {
		//cout << data << " < " << subRoot->data << ", trying left tree..." << endl;
		bool returnVal = add(data, subRoot->left);
		updateHeight(subRoot);
		rebalance(subRoot);
		return returnVal;
	}
	else if (data > subRoot->data) {
		//cout << data << " > " << subRoot->data << ", trying right tree..." << endl;
		bool returnVal = add(data, subRoot->right);
		updateHeight(subRoot);
		rebalance(subRoot);
		return returnVal;
	}
	else {	//data == subRoot->data
		//cout << data << " = " << subRoot->data << ", returing false..." << endl;
		return false;
	}
}

bool AVL::remove(int data, Node* &subRoot) { //FIXME
	//cout << "In remove. Attempting to remove " << data << " from subtree with root ";
	//if (subRoot == NULL) {cout << "NULL..." << endl;}
	//else {cout << subRoot->data << "..." << endl;}

	if (subRoot == NULL) {
		//cout << "Empty tree. Returning false..." << endl;
		return false;
	}

	else if (data < subRoot->data) {
		//cout << data << " < " << subRoot->data << ", trying left tree..." << endl;
		return remove(data, subRoot->left);
		//FIXME: update height
		//FIXME: rebalance
	}

	else if (data > subRoot->data) {
		//cout << data << " > " << subRoot->data << ", trying right tree..." << endl;
		return remove(data, subRoot->right);
		//FIXME: update height
		//FIXME: rebalance
	}
	//FIXME: update height, rebalance throughout the rest of this function
	else {	//data==subRoot->data (subRoot is the node to remove)
		//cout << data << " = " << subRoot->data << ", removing..." << endl;
		if (subRoot->left == NULL) {
			//cout << "Left subtree is empty. Replacing " << subRoot->data << " with ";
			Node* oldNode = subRoot;
			subRoot = subRoot->right;
			//if (subRoot == NULL) {cout << "NULL";}
			//else {cout << subRoot->data;}
			//cout << " and deleting " << oldNode->data << "." << endl;
			delete oldNode;
		}

		else if (subRoot->right == NULL) {
			//cout << "Right subtree is empty. Replacing " << subRoot->data << " with ";
			Node* oldNode = subRoot;
			subRoot = subRoot->left;
			//if (subRoot == NULL) {cout << "NULL";}
			//else {cout << subRoot->data;}
			//cout << " and deleting " << oldNode->data << "." << endl;
			delete oldNode;
		}

		else {
			//Find the rightmost local root to the left of subRoot that does not have a right child
			//cout << "Neither subtree is empty." << endl;
			Node* replacementNode = subRoot->left;
			while (replacementNode->right != NULL) {
				replacementNode = replacementNode->right;
			}
			//cout << "Replacement node is " << replacementNode->data << endl;
			//Put its value into subRoot, then remove it (from subRoot's left subtree)
			subRoot->data = replacementNode->data;
			//cout << "subRoot is now " << subRoot->data << endl;
			//cout << "Removing duplicate value from left subtree." << endl;
			remove(subRoot->data, subRoot->left);
		}
	//cout << "Returning true..." << endl;
	return true;
	}
}

int AVL::getHeight(Node* n) {
	if (n == NULL) {
		return 0;
	}
	else {
		return n->height;
	}
}

int AVL::updateHeight(Node* n, bool recursive) {
	if (n == NULL) {
		return 0;
	}

	int l_child_height;
	int r_child_height;

	if(recursive) {
		l_child_height = updateHeight(n->left, true);
		r_child_height = updateHeight(n->right, true);
	}
	else {
		l_child_height = getHeight(n->left);
		r_child_height = getHeight(n->right);
	}

	if (l_child_height > r_child_height) {
		n->height = (1 + l_child_height);
	}
	else {
		n->height = (1 + r_child_height);
	}

	return n->height;
}

int AVL::getBalance(Node* n) {
	if (n == NULL) {return 0;}
	return (getHeight(n->right) - getHeight(n->left));
}

void AVL::rotateLeft(Node* &n) {
	if (n->right == NULL) {
		throw "Error: Node has no right child!";
	}
	Node* temp = n->right;
	n->right = temp->left;
	temp->left = n;
	n = temp;
	updateHeight(n, true);
}

void AVL::rotateRight(Node* &n) {
	if (n->left == NULL) {
		throw "Error: Node has no left child!";
	}
	Node* temp = n->left;
	n->left = temp->right;
	temp->right = n;
	n = temp;
	updateHeight(n, true);
}

void AVL::rebalance(Node* &n) {
	/*if (n == NULL) {
		throw "Error: Cannot rebalance, node is NULL!";
	}*/ //Unneccesary?
	int balance = getBalance(n);
	if (balance < -2 || balance > 2) {
		throw "Error: Node is unbalanced by more than 2!";
	}
	if (balance >= -1 && balance <= 1) {
		return; //Node is sufficiently balanced
	}

	if (balance == -2) { //Left-heavy
		int l_balance = getBalance(n->left);
		if (l_balance < -1 || l_balance > 1) {
			throw "Error: Left child is unbalanced by more than 1!";
		}
		if (l_balance == -1 || l_balance == 0) { //Left-left tree
			rotateRight(n);
			return;
		}
		else { //Left-right tree
			rotateLeft(n->left);
			rotateRight(n);
			return;
		}
	}

	if (balance == 2) { //Right-heavy
		int r_balance = getBalance(n->right);
		if (r_balance < -1 || r_balance > 1) {
			throw "Error: Right child is unbalanced by more than 1!";
		}
		if (r_balance == 0 || r_balance == 1) { //Right-right tree
			rotateLeft(n);
			return;
		}
		else { //Right-left tree
			rotateRight(n->right);
			rotateLeft(n);
			return;
		}
	}
}

#endif