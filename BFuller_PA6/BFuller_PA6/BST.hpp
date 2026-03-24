#pragma once
#include "BSTNode.hpp"
#include <fstream>
#include <iostream>

template <typename C, typename S>
class BST
{
public:
	BST();
	~BST();

	/* Public Tree Operation Access Points */
	void insert(const C key, const S val);
	void printInOrder() const;
	S search(C key) const;

private:
	BSTNode<C, S>* mpRoot;

	/* Tree Operation Implementation */
	void insert(BSTNode<C, S>*& pTree, C key, S val);
	void destroyTree(BSTNode<C, S>* pTree);
	void printInOrder(BSTNode<C, S>* pTree) const;
	S search(BSTNode<C, S>* pTree, C key) const;
};

#include "BST.cpp"