#include <iostream>
#include <cstring>
using namespace std;

class IQueue {
public:
	virtual ~IQueue() = default;
	virtual void Clear() = 0;
	virtual bool IsEmpty() = 0;
	virtual bool IsFull() = 0;
	virtual void Enqueue(int value) = 0;
	virtual int Dequeue() = 0;
	virtual int GetFirstElement() = 0;
};

/*
// Function displaying the elements of Circular Queue
void displayQueue(struct Queue *q)
{
struct Node *temp = q->front;
printf("\nElements in Circular Queue are: ");
while (temp->link != q->front)
{
printf("%d ", temp->data);
temp = temp->link;
}
printf("%d", temp->data);
}*/



class CircularList : public IQueue {
private:
	struct Node {
		int data;
		struct Node* link;
	};
	struct Node *first, *last;
public:
	CircularList() {
		first = last = NULL;
	}

	~CircularList() {
		Clear();
	}

	bool IsEmpty() {
		return ((first == NULL));
	}

	bool IsFull() {
		return 0;
	}

	void Clear() {
		// delete all the nodes alloted
		struct Node *temp = first;
		while ((temp) && (first != last)) {
			first = first->link;
			last->link = first;
			free(temp);
			temp = first;
		}
		free(temp);
		first = last = NULL;
	}
	void Enqueue(int value);
	int Dequeue();
	int GetFirstElement();
};

class CircularQueue : public IQueue {
public:
	CircularQueue(int s) {
		ind_first = ind_last = -1;
		contents = new int(size);
		size = s;
	}

	~CircularQueue() {
		delete contents;
	}

	bool IsEmpty() {
		return ((ind_first == -1));
	}

	bool IsFull() {
		return (ind_first == (ind_last + 1) % size);
	}

	void Clear() {
		ind_first = ind_last = -1;
		memset(contents, 0, size);
	}

	void Enqueue(int value);
	int Dequeue();
	int GetFirstElement();
private:
	int ind_first, ind_last, size;
	int *contents;
};


class ArrayQueue : public IQueue {
public:
	ArrayQueue(int s) {
		ind_first = ind_last = -1;
		contents = new int(size);
		size = s;
	}

	~ArrayQueue() {
		delete contents;
	}

	bool IsEmpty() {
		return ind_first == -1;
	}
	bool IsFull() {
		return ((ind_first == 0) && (ind_last == size - 1) || (ind_first == ind_last + 1));
	}

	void Clear() {
		ind_first = ind_last = -1;
		memset(contents, 0, size);
	}

	void Enqueue(int value);
	int Dequeue();
	int GetFirstElement();
private:
	int ind_first, ind_last, size;
	int *contents;
};

void ArrayQueue::Enqueue(int value) {
	if (!IsFull()) {
		if (ind_last == size - 1 || ind_last == -1) {
			contents[0] = value;
			ind_last = 0;
			if (ind_first == -1)
				ind_first = 0;
		}
		else {
			contents[++ind_last] = value;
		}
	}
}

int ArrayQueue::Dequeue() {
	int tmp = contents[ind_first];
	if (ind_first == ind_last) {
		ind_last = ind_first = -1;
	}
	else if (ind_first == size - 1) {
		ind_first = 0;
	}
	else {
		ind_first++;
	}
	return tmp;
}
int ArrayQueue::GetFirstElement() {
	if (!IsEmpty())
		return contents[ind_first];
	return -1;
}



void CircularQueue::Enqueue(int value) {
	if (!IsFull()) {
		if (ind_first == -1) {
			ind_first = 0;
			ind_last = 0;
		}
		else {
			if (ind_last == size - 1)
				ind_last = 0;
			else
				ind_last++;
		}
		contents[ind_last] = value;
	}
}

int CircularQueue::Dequeue() {
	if (IsEmpty()) return -1;

	int tmp = contents[ind_first];

	if (ind_first == ind_last) {
		ind_first = ind_last = -1;
	}
	else {
		if (ind_first == size - 1) {
			ind_first = 0;
		}
		else
			ind_first++;
	}
	return tmp;
}
int CircularQueue::GetFirstElement() {
	if (!IsEmpty())
		return contents[ind_first];
	return -1;
}


// Function to create Circular queue 
void CircularList::Enqueue(int value)
{
	struct Node *temp = new struct Node;
	temp->data = value;

	if (first == NULL)
		first = temp;
	else
		last->link = temp;

	last = temp;
	last->link = first;
}

// Function to delete element from Circular Queue 
int CircularList::Dequeue() {
	if (IsEmpty())
		return -1;

	// If this is the last node to be deleted 
	int value; // Value to be dequeued 
	if (first == last) {
		value = first->data;
		delete first;
		first = NULL;
		last = NULL;
	}
	else {
		// There are more than one nodes 
		struct Node *temp = first;
		value = temp->data;
		first = first->link;
		last->link = first;
		free(temp);
	}
	return value;
}

int CircularList::GetFirstElement() {
	if (!IsEmpty())
		return first->data;
	return -1;
}
int main() {
	// Choose the data structure to be used for the implementation

	int option = 1;

	IQueue *queue = NULL;
	cout << "Choose the Desired Data Type for Queue Implementation" << endl;
	cout << "1. Circular List " << endl;
	cout << "2. Circular Array" << endl;
	cout << "3. Regular Array" << endl;
	cout << "0. Exit" << endl;
	cout << "Please input your option:";
	cin >> option;

	switch (option) {
	case 0:
		break;
	case 1: {
		CircularList *q = new CircularList();
		queue = q;
	}
			break;
	case 2: {
		CircularQueue *q = new CircularQueue(5);
		queue = q;
	}
			break;
	case 3: {
		ArrayQueue *q = new ArrayQueue(5);
		queue = q;
	}
			break;
	default:
		cout << "Select a valid option";
		option = 0;
		break;
	}

	while (option && queue != NULL) {
		cout << "Choose the Desired operation on the Queue" << endl;
		cout << "1. Insert " << endl;
		cout << "2. Delete" << endl;
		cout << "3. Clear" << endl;
		cout << "4.Get First Item" << endl;
		cout << "0. Exit" << endl;
		cout << "Please input your option:";
		cin >> option;

		int value;
		switch (option) {
		case 0:
			break;
		case 1: {
			cout << "enter the value to insert: " << endl;
			cin >> value;
			queue->Enqueue(value);
		}
				break;
		case 2: {
			cout << "The Deleted Item is " << queue->Dequeue() << endl;
		}
				break;
		case 3: {
			queue->Clear();
			cout << "The Queue is Cleared" << endl;
		}
				break;
		case 4: {
			cout << "The First Item is :" << queue->GetFirstElement() << endl;
		}
				break;
		default:
			cout << "Select a valid option";
			option = 5;
			break;
		}

	}

	queue->Enqueue(30);
	queue->Enqueue(40);
	queue->Enqueue(50);
	queue->Enqueue(60);
	queue->Enqueue(70);

	cout << queue->Dequeue();
	cout << queue->Dequeue();
	cout << queue->Dequeue();
	cout << queue->Dequeue();
	cout << queue->Dequeue();

	delete queue;
}
