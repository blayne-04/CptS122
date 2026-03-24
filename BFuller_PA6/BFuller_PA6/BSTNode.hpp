#pragma once

template <typename C, typename S>
class BSTNode
{
public:
	BSTNode(): mpLeft(nullptr), mpRight(nullptr), mVal(S()), mKey(C()) {}

	BSTNode(C key, S val) : mpLeft(nullptr), mpRight(nullptr), mVal(val), mKey(key) {}

	~BSTNode(){}

	S getVal() const { return mVal; }
	C getKey() const { return mKey; }

	// Returns reference to, non-const
	BSTNode<C, S>*& getLeft() { return mpLeft; }
	BSTNode<C, S>*& getRight() { return mpRight; }

	// Returns ptr to, const-friendly
	BSTNode<C, S>* getLeft() const{ return mpLeft; }
	BSTNode<C, S>* getRight() const { return mpRight; }

	void setLeft(BSTNode<C, S>* leftNode) { mpLeft = leftNode; }
	void setRight(BSTNode<C, S>* rightNode) { mpRight = rightNode; }

	void setVal(const S val) { mVal = val; }
	void setKey(const C key) { mKey = key; }

private:
	S mVal;
	C mKey;
	BSTNode<C, S>* mpLeft,
		* mpRight;
};