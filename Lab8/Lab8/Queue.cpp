#include "Queue.hpp"

Queue::Queue() {
	this->mpHead = this->mpTail = nullptr;
}

Queue::~Queue() {}

std::string Queue::dequeue() {
	QueueNode* pTemp = mpHead;
	std::string temp = pTemp->getData(); // Pull the data to return

	if (mpHead != mpTail) {
		mpHead = mpHead->getNext(); // Assign head ptr to next ptr in list
	}
	else {
		mpHead = mpTail = nullptr;
	}

	delete pTemp; // Delete mpHead

	return temp; // Return the data from the old head
}

bool Queue::enqueue(const std::string& data) {
	//Instantiate a new node and initialize it's values
	QueueNode* pMem = new QueueNode(data);
	bool success = false;

	if (pMem != nullptr) {
		success = true; //If we allocated successfully, we were successful

		if (mpHead == nullptr) { //If the list is empty
			this->mpHead = this->mpTail = pMem; //Set head and tail to the new node
		}
		else { //Not an empty queue, set the tail's mpNext to new node
			mpTail->setNext(pMem);
			mpTail = pMem; //then set the tail ptr to the new node
		}
	}
	return success;
}

bool Queue::isEmpty() {
	return (mpHead == nullptr) ? true : false;
}

void Queue::destroyQueue() {
	while (!isEmpty()) {
		dequeue();
	}
}

void Queue::printQueueRecursive(QueueNode* pCur)
{
	if (pCur == nullptr)
	{
		return;
	}
	std::cout << pCur->getData() << std::endl;
	printQueueRecursive(pCur->getNext());
}