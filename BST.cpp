#include "BST.h"
#include <iostream>

void insert_integer(Node** tree, int value)
{
	// If the current node is empty, create a new object in memory.
	if (*tree == nullptr)
	{
		*tree = new Node;
		(*tree)->value = value;
		return;
	}

	// If the value of the node is greater than the current node's value, the node should be placed on the right child of the current node; otherwise it should be the left child.
	value > (*tree)->value ? insert_integer(&(*tree)->right, value) : insert_integer(&(*tree)->left, value);
}

void print_tree(Node* tree)
{
	// Using inorder traversal, we can print every value to the console.
	if (tree == nullptr)
		return;

	print_tree(tree->left);

	std::cout << tree->value << " ";

	print_tree(tree->right);
}

void terminate_tree(Node* tree)
{
	if (tree != nullptr)
	{
		if (tree->left != nullptr)
			terminate_tree(tree->left);
		if (tree->right != nullptr)
			terminate_tree(tree->right);

		delete tree;
		tree = nullptr;
	}
}

int most_common_integer(Node* tree)
{
	if (tree == nullptr)
		return 0;

	most_common_integer(tree->left);

	if (previous != nullptr)
		tree->value == previous->value ? count++ : count = 1;

	if (count > maxCount)
	{
		maxCount = count;
		mNumber = tree->value;
	}

	previous = tree;
	most_common_integer(tree->right);
	return mNumber;
}

int largest_integer(Node* tree)
{
	if (tree == nullptr)
		return 0;

	int maxInt = tree->value;
	int leftNodeInt = largest_integer(tree->left);
	int rightNodeInt = largest_integer(tree->right);

	if (leftNodeInt > maxInt)
		maxInt = leftNodeInt;

	if (rightNodeInt > maxInt)
		maxInt = rightNodeInt;

	return maxInt;
}

int sum_of_all_integers(Node* tree)
{
	if (tree == nullptr)
		return 0;

	return tree->value + sum_of_all_integers(tree->left) + sum_of_all_integers(tree->right);
}