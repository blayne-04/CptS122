#pragma once

#include "QueueNode.hpp"
#include <iostream>
#include <string>

class QueueNode 
{

public:

	QueueNode();
	QueueNode(const std::string data);
	QueueNode(QueueNode* &q);
	~QueueNode();

	void setData(const std::string data);
	std::string getData() const;

	void setNext(QueueNode* &ptr);
	QueueNode* getNext() const;

private:
	std::string mData;
	QueueNode* mpNext;
};