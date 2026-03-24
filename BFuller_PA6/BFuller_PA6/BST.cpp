#include "BST.hpp"

template <typename C, typename S>
BST<C, S>::BST()
{
	mpRoot = nullptr;
	std::ifstream inFile("MorseTable.txt");

	C tempKey;
	S tempVal;

	if (inFile.is_open()) 
	{
		std::cout << "Temp Debug Code" << std::endl;
		while (inFile >> tempKey >> tempVal)
		{
			std::cout << tempKey << tempVal << std::endl;
			insert(tempKey, tempVal);
		}

		inFile.close();
	}
	else
	{
		std::cout << "Morse Table Did Not Open!" << std::endl;
	}
}

template <typename C, typename S>
BST<C, S>::~BST()
{
	destroyTree(mpRoot);
}

/* Public Tree Operation Access Points */
template<typename C, typename S>
void BST<C, S>::insert(const C key, const S val)
{
	insert(mpRoot, key, val);
}

template<typename C, typename S>
void BST<C, S>::printInOrder() const
{
	printInOrder(mpRoot);
}

template<typename C, typename S>
S BST<C, S>::search(C key) const
{
	return search(mpRoot, key);
}

/* Tree Operation Implementation (Member Functions For Internal Recursion) */
template<typename C, typename S>
void BST<C, S>::insert(BSTNode<C, S>*& pTree, C key, S val)
{
	if (pTree == nullptr)
	{
		pTree = new BSTNode<C, S>(key, val);
	}
	else
	{
		if (pTree->getKey() == key)
		{
			std::cout << "This character is already accounted for by the database" << std::endl;
			return;
		}
		else if (pTree->getKey() > key)
		{
			insert(pTree->getLeft(), key, val);
		}
		else if (pTree->getKey() < key)
		{
			insert(pTree->getRight(), key, val);
		}
	}
}

template<typename C, typename S>
S BST<C, S>::search(BSTNode<C, S>* pTree, C key) const
{
	if (pTree == nullptr) return S();

	if (pTree->getKey() == key)
	{
		return pTree->getVal();
	}
	else 
	{
		if (pTree->getKey() < key)
		{
			return search(pTree->getRight(), key);
		}
		else if (pTree->getKey() > key)
		{
			return search(pTree->getLeft(), key);
		}
	}
}

/* Credit: Adapted From Geeks for Geeks, Deletes BST in order, left -> right -> root */
template<typename C, typename S>
void BST<C, S>::destroyTree(BSTNode<C, S>* pTree)
{
	if (pTree == nullptr) return;

	destroyTree(pTree->getLeft());
	destroyTree(pTree->getRight());

	delete pTree;
}

/* Credit: Adapted From Geeks for Geeks, Prints BST in order, left -> root -> right */
template<typename C, typename S>
void BST<C, S>::printInOrder(BSTNode<C, S>* pTree) const
{
	if (pTree == nullptr) return;

	printInOrder(pTree->getLeft());

	std::cout << pTree->getKey() << ":" << pTree->getVal() << std::endl;

	printInOrder(pTree->getRight());
}