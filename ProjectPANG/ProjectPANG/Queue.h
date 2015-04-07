
#ifndef __Queue_H__
#define __Queue_H__

template <class DoubleNodeDataTYPE>struct DoubleNode
{
	DoubleNodeDataTYPE data;
	DoubleNode* previous;
	DoubleNode* next;

	inline DoubleNode(const DoubleNodeDataTYPE& item)
	{
		data = item;
		next = previous = NULL;
	}

	~DoubleNode(){}
};

template <class QueueTYPE> class DoubleNodedQueue
{
private:

	DoubleNode<QueueTYPE>* init;
	DoubleNode<QueueTYPE>* last;

public:

	inline DoubleNodedQueue(){ init = last = NULL; }

	~DoubleNodedQueue(){ clear(); }

	DoubleNode<QueueTYPE>* getStart(){ return init; }

	DoubleNode<QueueTYPE>* getLast(){ return last; }

	void push(const QueueTYPE& data)
	{
		DoubleNode<QueueTYPE>* node;
		node = new DoubleNode<QueueTYPE>(data);
		if (init == NULL)
		{
			last = init = node;
		}
		else
		{
			node->previous = last;
			last->next = node;
			last = last->next;
		}
	}

	void clear()
	{
		while (init != NULL)
		{
			delete init->data;
			init = init->next;
		}
		last = NULL;
	}

	void ReduceTo(const unsigned int quantity)
	{
		DoubleNode<QueueTYPE>* tmp = init;

		for (int i = 0; i < quantity; i++){ node = node->next; }

		while (node->data != last)
		{
			last = last->previous;
			delete[] last->next;
		}

		node->next = last;
		last->next = NULL;

		delete tmp;
	}

};

#endif