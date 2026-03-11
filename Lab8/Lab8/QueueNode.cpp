#include "QueueNode.hpp"

QueueNode::QueueNode()
{
	mData = "";
}

QueueNode::QueueNode(const std::string data)
{
	mData = data;
}

QueueNode::QueueNode(QueueNode*& q)
{
	mData = q->getData();
}

QueueNode::~QueueNode()
{
	delete this;
}

void QueueNode::setData(const std::string data)
{
	mData = data;
}

std::string QueueNode::getData() const
{
	return std::string();
}

void QueueNode::setNext(QueueNode* &ptr)
{
	mpNext = ptr;
}

QueueNode* QueueNode::getNext() const
{
	return mpNext;
}
