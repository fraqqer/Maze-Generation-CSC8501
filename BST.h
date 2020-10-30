#pragma once

#ifndef BST_H
#define BST_H

struct Node
{
	int value = 0;
	struct Node* left = nullptr;
	struct Node* right = nullptr;
};

struct Node* previous = nullptr;

void insert_integer(struct Node** tree, int value);
void print_tree(struct Node* tree);
void terminate_tree(struct Node* tree);
int most_common_integer(struct Node* tree);
int largest_integer(struct Node* tree);
int sum_of_all_integers(struct Node* tree);

int count = 1;
int maxCount = 0;
int mNumber;

#endif