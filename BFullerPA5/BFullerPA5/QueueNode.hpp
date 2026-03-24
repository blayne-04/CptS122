#pragma once

#include "Data.hpp"

class QueueNode 
{
public:
	QueueNode();
	QueueNode(QueueNode* q);
	QueueNode(Data* data);

	~QueueNode();

	Data* getData() const;
	void setData(Data* data);

	QueueNode* getNext() const;
	void setNext(QueueNode* pNext);

private:
	Data mData;
	QueueNode* mpNext;

};