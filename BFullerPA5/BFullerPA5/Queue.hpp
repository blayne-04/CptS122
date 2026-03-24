#pragma once

#include <iostream>
#include "QueueNode.hpp"

class Queue
{
public:
	Queue();
	~Queue() { destroyQueue(); }

	std::string dequeue();
	bool enqueue(const std::string& data);

	bool isEmpty();

	void destroyQueue();
	void printQueueRecursive(QueueNode* pCur);

private:
	QueueNode* mpHead,
		* mpTail;

};